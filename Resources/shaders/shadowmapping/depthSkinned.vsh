attribute vec4 a_position;
attribute vec4 a_blendWeight;
attribute vec4 a_blendIndex;

const int SKINNING_JOINT_COUNT = 60;
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];
// v2f
varying float depth;


void getPosition(out vec4 position)
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

}


void main(void)
{
	vec4 skinned_position;
	getPosition(skinned_position);
	gl_Position = CC_MVPMatrix * skinned_position;
	depth = gl_Position.z;
	// depth = gl_Position.z;
	// depth = gl_Position.z;
	// float depth = 1;
}