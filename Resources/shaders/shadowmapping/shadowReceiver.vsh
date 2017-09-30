attribute vec4 a_position;
attribute vec2 a_texCoord;

uniform mat4 _object2World;
uniform mat4 _depthVPBias;
uniform mat4 _depthVP;

// v2f
varying vec4 v2f_shadowCoord;
varying vec2 v2f_uv;
varying float depth;
void main(void)
{
	gl_Position = CC_MVPMatrix * a_position;
	vec4 worldPos = _object2World * a_position;
	v2f_shadowCoord = _depthVPBias * worldPos;
	v2f_shadowCoord.z = (_depthVP * worldPos).z;
	v2f_uv = a_texCoord;
	// gl_Position = _depthVP * worldPos;
	// depth = gl_Position.z;
	// float depth = 1;
}