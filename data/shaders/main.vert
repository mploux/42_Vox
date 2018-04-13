#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in int in_faces;

uniform mat4 projectionMatrix;

out vec3 v_position;
out vec4 v_trs;

out int v_faces;

void main()
{
	v_position = in_position;

	v_faces = in_faces;

	v_trs = projectionMatrix * vec4(in_position, 1.0);
	gl_Position = projectionMatrix * vec4(in_position, 1.0);
}