attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
attribute vec3 a_tangent;
attribute vec3 a_binormal;

uniform mat4 _object2World;
uniform mat4 _world2Object;
uniform vec3 u_color;

// v2f
varying vec4 v2f_posWorld;
varying vec2 v2f_tex;
varying vec3 v2f_tangentWorld;
varying vec3 v2f_normalWorld;
varying vec3 v2f_binormalWorld;
// end v2f

void main(void)
{
	v2f_posWorld = (_object2World * a_position);
	v2f_tangentWorld = normalize(mat3(_object2World) * a_tangent.xyz);
	v2f_normalWorld = normalize(a_normal.xyz * mat3(_world2Object));
	v2f_binormalWorld = normalize(mat3(_object2World) * a_binormal.xyz);
	// v2f_binormalWorld = normalize(cross(v2f_normalWorld, v2f_tangentWorld));

	v2f_tex = a_texCoord;
	gl_Position = CC_MVPMatrix * a_position;

}