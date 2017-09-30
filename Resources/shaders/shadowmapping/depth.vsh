attribute vec4 a_position;
// v2f
varying float depth;

void main(void)
{
	gl_Position = CC_MVPMatrix * a_position;
	depth = gl_Position.z;
	// depth = gl_Position.z;
	// depth = gl_Position.z;
	// float depth = 1;
}