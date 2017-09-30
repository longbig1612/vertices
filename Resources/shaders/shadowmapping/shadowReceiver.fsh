uniform sampler2D _shadowmap;
uniform float _shadowBias;
uniform float _shadowStrength;
uniform float _texmapScale;
// v2f
varying vec4 v2f_shadowCoord;
varying vec2 v2f_uv;
varying float depth;

vec4 offset_lookup(sampler2D tex, vec4 texCoord, vec2 offset)
{
	return texture2D(tex, texCoord.xy + offset * _texmapScale);
}

float shade(sampler2D tex, vec4 texCoord, vec2 offset) 
{
	float depthLookup = offset_lookup(tex, texCoord, offset).z;
	float shade = max(step(texCoord.z - _shadowBias, depthLookup), _shadowStrength);
	return shade;
}

float hardShadow() 
{
	return shade(_shadowmap, v2f_shadowCoord, vec2(0.0));
}

float PCF4Samples() 
{
	float sum = 0.0;
	vec2 offset = vec2(step(0.25, fract(v2f_shadowCoord.xy * 0.5)));
	offset.y += offset.x;
	sum += shade(_shadowmap, v2f_shadowCoord, offset + vec2(-1.5,0.5));
	sum += shade(_shadowmap, v2f_shadowCoord, offset + vec2(0.5,0.5));
	sum += shade(_shadowmap, v2f_shadowCoord, offset + vec2(-1.5,-1.5));
	sum += shade(_shadowmap, v2f_shadowCoord, offset + vec2(0.5,-1.5));
	sum = sum / 4.0;
	return sum;
}

void main()
{
	vec4 col = texture2D(CC_Texture0, v2f_uv.xy);
	// float shade = hardShadow();
	float shade = PCF4Samples();
	gl_FragColor.rgb = vec3(shade * col.rgb);
	gl_FragColor.a = 1.0;
}