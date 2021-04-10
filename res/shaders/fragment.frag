#version 400
in vec3 color;
in vec2 textureCoord;
out vec4 frag_color;

uniform sampler2D texture_image;

void main(){
   frag_color = texture(texture_image,textureCoord);
}