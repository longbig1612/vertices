uniform sampler2D _lightmap;
uniform float _lightmapscale;


varying vec2 v2f_texcoord;
varying vec2 v2f_texcoord1;

void main()
{
	vec4 col = texture2D(CC_Texture0, v2f_texcoord);
	vec4 diffuse = texture2D(_lightmap, v2f_texcoord1) * _lightmapscale;
	col.rgb *= diffuse.rgb;
	//col = col * 2;
	gl_FragColor = col;
	
}