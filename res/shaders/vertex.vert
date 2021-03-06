#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec2 texture_coord;
out vec3 color;
out vec2 textureCoord;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main(){
   color = vertex_color;
   textureCoord = texture_coord;
   gl_Position = projectionMatrix * modelMatrix * vec4(vertex_position,1.0);
}