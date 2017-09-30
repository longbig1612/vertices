attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
attribute vec3 a_tangent;
attribute vec3 a_binormal;
attribute vec4 a_blendWeight;
attribute vec4 a_blendIndex;

uniform mat4 _object2World;
uniform mat4 _world2Object;
uniform vec3 u_color;
const int SKINNING_JOINT_COUNT = 60;
// Uniforms
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];


// v2f
varying vec4 v2f_posWorld;
varying vec2 v2f_tex;
varying vec3 v2f_tangentWorld;
varying vec3 v2f_normalWorld;
varying vec3 v2f_binormalWorld;
// end v2f

void getPositionAndNormal(out vec4 position, out vec4 normal, out vec4 tangent, out vec4 binormal)
{
    float blendWeight = a_blendWeight[0];

    int matrixIndex = int (a_blendIndex[0]) * 3;
    vec4 matrixPalette1 = u_matrixPalette[matrixIndex] * blendWeight;
    vec4 matrixPalette2 = u_matrixPalette[matrixIndex + 1] * blendWeight;
    vec4 matrixPalette3 = u_matrixPalette[matrixIndex + 2] * blendWeight;

    blendWeight = a_blendWeight[1];
    matrixIndex = int(a_blendIndex[1]) * 3;
    matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
    matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
    matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;

    blendWeight = a_blendWeight[2];
	matrixIndex = int(a_blendIndex[2]) * 3;
    matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
    matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
    matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;

    blendWeight = a_blendWeight[3];
 	matrixIndex = int(a_blendIndex[3]) * 3;
    matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
    matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
    matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;

    vec4 p = a_position;
    position.x = dot(p, matrixPalette1);
    position.y = dot(p, matrixPalette2);
    position.z = dot(p, matrixPalette3);
    position.w = p.w;

    vec4 n = vec4(a_normal, 0.0);
    normal.x = dot(n, matrixPalette1);
    normal.y = dot(n, matrixPalette2);
    normal.z = dot(n, matrixPalette3);

    vec4 t = vec4(a_tangent, 0.0);
    tangent.x = dot(t, matrixPalette1);
    tangent.y = dot(t, matrixPalette2);
    tangent.z = dot(t, matrixPalette3);

    vec4 b = vec4(a_binormal, 0.0);
    binormal.x = dot(b, matrixPalette1);
    binormal.y = dot(b, matrixPalette2);
    binormal.z = dot(b, matrixPalette3);
}


void main(void)
{
	vec4 skinned_position;
    vec4 skinned_normal;
    vec4 skinned_tangent;
    vec4 skinned_binormal;
    getPositionAndNormal(skinned_position, skinned_normal, skinned_tangent, skinned_binormal);

	v2f_posWorld = (_object2World * skinned_position);
	v2f_tangentWorld = normalize(mat3(_object2World) * skinned_tangent.xyz);
	v2f_normalWorld = normalize(skinned_normal.xyz * mat3(_world2Object));
	v2f_binormalWorld = normalize(mat3(_object2World) * skinned_binormal.xyz);

	v2f_tex = a_texCoord;
	gl_Position = CC_MVPMatrix * skinned_position;

}