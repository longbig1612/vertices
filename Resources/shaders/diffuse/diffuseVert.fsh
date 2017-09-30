
// v2f
varying vec2 v2f_tex;
varying vec3 v2f_diffuse;
// end v2f

void main()
{
	vec4 col = texture2D(CC_Texture0, v2f_tex);
	gl_FragColor = col * vec4(v2f_diffuse,1.0);
	// gl_FragColor = vec4(1);
}