#version 400 core

layout (location = 0) in vec3 in_position;

uniform mat4 projectionMatrix;

out vec3 v_position;

void main()
{
	v_position = in_position;
	gl_Position = projectionMatrix * vec4(in_position, 1.0);
}