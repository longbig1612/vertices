attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_normal;

uniform mat4 _world2Object;
uniform vec3 u_color;
uniform vec3 _LightDir0;
uniform vec3 _LightColor0;
// v2f
varying vec2 v2f_tex;
varying vec3 v2f_diffuse;
// end v2f

void main(void)
{
	vec3 normalWorld = normalize(a_normal.xyz * mat3(_world2Object));
	v2f_tex = a_texCoord;
	gl_Position = CC_MVPMatrix * a_position;
	v2f_diffuse = _LightColor0 * (0.5 * dot(normalWorld, _LightDir0) + 0.5);
}