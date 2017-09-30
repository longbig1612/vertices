attribute vec2 a_position;
attribute vec2 a_texCoord;
attribute vec2 a_texCoord1;
//attribute vec2 a_texCoord2;
//attribute vec2 a_texCoord3;
//attribute vec2 flagg;

// Output data ; will be interpolated for each fragment.
varying vec2 UV;
varying vec2 flag;

void main(void){
    gl_Position = vec4(a_position.x, -a_position.y, 0, 1);
    UV = vec2(a_texCoord.x, a_texCoord.y);
    flag = a_texCoord1;
}
