attribute vec4 a_position;
attribute vec4 a_texCoord;

// v2f
varying vec2 v2f_texcoord;

void main(void)
{
	gl_Position = CC_MVPMatrix * a_position;
	v2f_texcoord = a_texCoord;
}