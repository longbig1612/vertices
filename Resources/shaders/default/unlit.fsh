varying vec2 v2f_texcoord;

void main()
{
	vec4 col = texture2D(CC_Texture0, v2f_texcoord);
	//col = col * 2;
	gl_FragColor = col;
	
}