// Interpolated values from the vertex shaders
varying vec2 UV;
varying vec2 UV2;

varying vec2 flag;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler1;
uniform sampler2D myTextureSampler2;

void main(){
    gl_FragColor = texture2D( myTextureSampler1, UV ).rgba * flag.x + flag.y * texture2D(myTextureSampler2, UV).rgba;
    //gl_FragColor = texture2D(myTextureSampler1, UV).rgba;
    //gl_FragColor = vec4(flag.x, flag.y, 0, 1);
}
