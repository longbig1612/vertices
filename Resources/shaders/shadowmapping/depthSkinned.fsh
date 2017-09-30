// v2f
varying float depth;

void main()
{
	gl_FragColor.rgb = vec3(depth);
	gl_FragColor.a = 1.0;
}