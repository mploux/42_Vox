#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in lowp int in_faces;

layout (location = 2) in lowp ivec2 in_tex_0;
layout (location = 3) in lowp ivec2 in_tex_1;
layout (location = 4) in lowp ivec2 in_tex_2;

uniform mat4 projectionMatrix;

out vec4 v_position;
out lowp int v_texture[6];

out vec4 v_trs;
out vec3 frag_pos;

out lowp int v_faces;

void main()
{
	v_position = vec4(in_position, 1.0);

	v_texture[0] = in_tex_0.x;
	v_texture[1] = in_tex_0.y;
	v_texture[2] = in_tex_1.x;
	v_texture[3] = in_tex_1.y;
	v_texture[4] = in_tex_2.x;
	v_texture[5] = in_tex_2.y;

	v_faces = in_faces;

	frag_pos = vec4(in_position, 1.0).xyz;
	v_trs = projectionMatrix * vec4(in_position, 1.0);
	gl_Position = projectionMatrix * vec4(in_position, 1.0);
}