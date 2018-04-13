#version 400 core

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

uniform mat4 projectionMatrix;

in vec4 v_trs[];
in lowp int v_faces[];
in vec4 v_position[];

out vec4 v_color;
out vec3 v_normal;
out vec2 v_texcoord;
out vec4 frag_position;

void addVertex(vec2 texcoord, vec3 offset)
{
	v_texcoord = texcoord;
	frag_position = (v_position[0] + vec4(offset.xyz, 0.0));
    gl_Position = projectionMatrix * frag_position;
    EmitVertex();
}

void draw_front()
{
	v_color = vec4(1, 0, 0, 1);
	v_normal = vec3(0, 0, -1);

	addVertex(vec2(0.0, 0.0), vec3(0.0, 1.0, 0.0));
	addVertex(vec2(1.0, 0.0), vec3(1.0, 1.0, 0.0));
	addVertex(vec2(0.0, 1.0), vec3(0.0, 0.0, 0.0));
	addVertex(vec2(1.0, 1.0), vec3(1.0, 0.0, 0.0));

    EndPrimitive();
}

void draw_back()
{
	v_color = vec4(1, 1, 0, 1);
	v_normal = vec3(0, 0, 1);

	addVertex(vec2(1.0, 1.0), vec3(0.0, 0.0, 1.0));
	addVertex(vec2(0.0, 1.0), vec3(1.0, 0.0, 1.0));
	addVertex(vec2(1.0, 0.0), vec3(0.0, 1.0, 1.0));
	addVertex(vec2(0.0, 0.0), vec3(1.0, 1.0, 1.0));

    EndPrimitive();
}

void draw_left()
{
	v_color = vec4(1, 1, 0, 1);
	v_normal = vec3(-1, 0, 0);

	addVertex(vec2(0.0, 1.0), vec3(0.0, 0.0, 1.0));
	addVertex(vec2(0.0, 0.0), vec3(0.0, 1.0, 1.0));
	addVertex(vec2(1.0, 1.0), vec3(0.0, 0.0, 0.0));
	addVertex(vec2(1.0, 0.0), vec3(0.0, 1.0, 0.0));

    EndPrimitive();
}

void draw_right()
{
	v_color = vec4(0, 1, 1, 1);
	v_normal = vec3(1, 0, 0);

	addVertex(vec2(0.0, 1.0), vec3(1.0, 0.0, 0.0));
	addVertex(vec2(0.0, 0.0), vec3(1.0, 1.0, 0.0));
	addVertex(vec2(1.0, 1.0), vec3(1.0, 0.0, 1.0));
	addVertex(vec2(1.0, 0.0), vec3(1.0, 1.0, 1.0));

    EndPrimitive();
}

void draw_bottom()
{
	v_color = vec4(0, 0, 1, 1);
	v_normal = vec3(0, -1, 0);

	addVertex(vec2(0.0, 0.0), vec3(0.0, 0.0, 0.0));
	addVertex(vec2(1.0, 0.0), vec3(1.0, 0.0, 0.0));
	addVertex(vec2(0.0, 1.0), vec3(0.0, 0.0, 1.0));
	addVertex(vec2(1.0, 1.0), vec3(1.0, 0.0, 1.0));

    EndPrimitive();
}

void draw_top()
{
	v_color = vec4(1, 0, 1, 1);
	v_normal = vec3(0, 1, 0);

	addVertex(vec2(0.0, 0.0), vec3(0.0, 1.0, 1.0));
	addVertex(vec2(1.0, 0.0), vec3(1.0, 1.0, 1.0));
	addVertex(vec2(0.0, 1.0), vec3(0.0, 1.0, 0.0));
	addVertex(vec2(1.0, 1.0), vec3(1.0, 1.0, 0.0));

    EndPrimitive();
}

void main()
{
	if ((v_faces[0] & (1 << 0)) != 0) draw_top();
	if ((v_faces[0] & (1 << 1)) != 0) draw_bottom();
	if ((v_faces[0] & (1 << 2)) != 0) draw_left();
	if ((v_faces[0] & (1 << 3)) != 0) draw_right();
	if ((v_faces[0] & (1 << 4)) != 0) draw_front();
	if ((v_faces[0] & (1 << 5)) != 0) draw_back();
}
