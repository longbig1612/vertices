attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec2 a_texCoord1;

// v2f
varying vec2 v2f_texcoord;
varying vec2 v2f_texcoord1;

void main(void)
{
	gl_Position = CC_MVPMatrix * a_position;
	v2f_texcoord = a_texCoord;
	v2f_texcoord1 = a_texCoord1;
}