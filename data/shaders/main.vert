#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in lowp int in_faces;

uniform mat4 projectionMatrix;

out vec4 v_position;
out vec4 v_trs;
out vec3 frag_pos;

out lowp int v_faces;

void main()
{
	v_position = vec4(in_position, 1.0);

	v_faces = in_faces;

	frag_pos = vec4(in_position, 1.0).xyz;
	v_trs = projectionMatrix * vec4(in_position, 1.0);
	gl_Position = projectionMatrix * vec4(in_position, 1.0);
}