uniform sampler2D _normalmap;
uniform sampler2D _maskmap1;
uniform sampler2D _maskmap2;
uniform float _rimlightscale;
uniform float _rimlightblendtofull;
uniform vec3 _rimlightcolor;
uniform float _diffusescale;
uniform float _selfillumblendtofull;

uniform float _specularexponent;
uniform float _specularblendtofull;
uniform vec3 _specularcolor;
uniform float _specularscale;
uniform mat4 _world2Object;
uniform vec3 u_color;

uniform vec3 _AmbientColor;
uniform vec3 _LightDir0;
uniform vec3 _LightColor0;
uniform vec3 _WorldSpaceCameraPos;
uniform mat4 _MATRIX_V;
// v2f
varying vec4 v2f_posWorld;
varying vec2 v2f_tex;
varying vec3 v2f_tangentWorld;
varying vec3 v2f_normalWorld;
varying vec3 v2f_binormalWorld;

// end v2f

void main()
{
	vec4 col = texture2D(CC_Texture0, v2f_tex);
	vec4 encodedNormal = texture2D(_normalmap, v2f_tex);
	vec4 _mask1 = texture2D(_maskmap1, v2f_tex);
	vec4 _mask2 = texture2D(_maskmap2, v2f_tex);
	vec3 localCoords = vec3( 2.0 * encodedNormal.x - 1.0, 2.0 * encodedNormal.y - 1.0, 0.0);
	localCoords.z = 1.0 - 0.5 * dot(localCoords, localCoords);

	mat3 local2WorldTranspose = mat3(
	v2f_tangentWorld,
	v2f_binormalWorld,
	v2f_normalWorld);

	vec3 normalDir = normalize(local2WorldTranspose * localCoords);
	// vec3 normalDir = v2f_normalWorld;
	vec3 lightDir = normalize(_LightDir0);
	vec3 viewDir = normalize(_WorldSpaceCameraPos - v2f_posWorld.xyz);

	float NdotL = dot(normalDir, lightDir);
	vec3 halfLambert = vec3(0.5 * NdotL + 0.5);
	vec3 diffuse = halfLambert * _LightColor0.rgb * _diffusescale + _AmbientColor;
	col.rgb *= diffuse;
	// col.rgb = v2f_normalWorld;

	vec3 fresnel = vec3(pow(1.0 - max(0.0, dot(normalDir, viewDir)), 5.0));
	// vec3 fresnel = vec3(pow(max(0.0,1.0 - max(0.0, dot(normalDir, viewDir))), 5.0));
	fresnel.b = 1.0 - fresnel.b;

	vec3 reflectionVec = normalize(2.0 * normalDir * halfLambert - lightDir);
	vec3 specular = _specularscale * 
					_mask2.r *
					NdotL * 
					_specularcolor * 
					fresnel.b *
					mix(col.rgb + vec3(_mask1.b), _specularcolor, _mask2.b) *
					_LightColor0.rgb * 
					pow(max(0.0, dot(reflectionVec, viewDir)), _specularexponent * _mask2.a);
	col.rgb += specular;

	// Metalness
	col.rgb = mix(col.rgb, specular, _mask1.b);

	// Rim light
	vec3 rimlight = _rimlightcolor *
					_rimlightscale *
					_mask2.g * 
					fresnel.r * 
					max(0.0, dot(_MATRIX_V[1].xyz, normalDir));

	col.rgb += rimlight;

	gl_FragColor = vec4(col.rgb,1.0);
}