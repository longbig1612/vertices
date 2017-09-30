// Interpolated values from the vertex shaders
varying vec2 UV;
varying vec2 UV2;

varying vec2 flag;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler1;

void main(){
    gl_FragColor = vec4(texture2D( myTextureSampler1, UV).rgb * flag.x, texture2D( myTextureSampler1, UV).a * flag.y);
    //gl_FragColor = vec4(flag.x, flag.y, 0, 1);
    //gl_FragColor = vec4(1, 0, 0, 1);
}
