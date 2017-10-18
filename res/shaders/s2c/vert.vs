#version 330 core

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

layout (location = 0) in vec3 vertices;

void main() {
	gl_Position = proj * view * model * vec4(vertices, 1.0);
}
