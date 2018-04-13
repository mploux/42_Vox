#version 400 core
#define TEXTURE_SIZE 16

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

uniform mat4 projectionMatrix;

in vec4 v_trs[];
in lowp int v_faces[];
in vec4 v_position[];
in lowp int v_texture[][6];

out vec4 v_color;
out vec3 v_normal;
out vec2 v_texcoord;
out vec4 frag_position;

void addVertex(vec2 texcoord, vec3 offset, float tx, float ty)
{
	v_texcoord = vec2((tx + texcoord.x) / TEXTURE_SIZE , (ty + texcoord.y) / TEXTURE_SIZE);
	frag_position = (v_position[0] + vec4(offset.xyz, 0.0));
    gl_Position = projectionMatrix * frag_position;
    EmitVertex();
}

void draw_top()
{
	v_color = vec4(1, 0, 1, 1);
	v_normal = vec3(0, 1, 0);

	float tx = v_texture[0][0] % TEXTURE_SIZE;
	float ty = v_texture[0][0] / TEXTURE_SIZE;

	addVertex(vec2(0.0, 0.0), vec3(0.0, 1.0, 1.0), tx, ty);
	addVertex(vec2(1.0, 0.0), vec3(1.0, 1.0, 1.0), tx, ty);
	addVertex(vec2(0.0, 1.0), vec3(0.0, 1.0, 0.0), tx, ty);
	addVertex(vec2(1.0, 1.0), vec3(1.0, 1.0, 0.0), tx, ty);

    EndPrimitive();
}

void draw_bottom()
{
	v_color = vec4(0, 0, 1, 1);
	v_normal = vec3(0, -1, 0);

	float tx = v_texture[0][1] % TEXTURE_SIZE;
	float ty = v_texture[0][1] / TEXTURE_SIZE;

	addVertex(vec2(0.0, 0.0), vec3(0.0, 0.0, 0.0), tx, ty);
	addVertex(vec2(1.0, 0.0), vec3(1.0, 0.0, 0.0), tx, ty);
	addVertex(vec2(0.0, 1.0), vec3(0.0, 0.0, 1.0), tx, ty);
	addVertex(vec2(1.0, 1.0), vec3(1.0, 0.0, 1.0), tx, ty);

    EndPrimitive();
}

void draw_left()
{
	v_color = vec4(1, 1, 0, 1);
	v_normal = vec3(-1, 0, 0);

	float tx = v_texture[0][2] % TEXTURE_SIZE;
	float ty = v_texture[0][2] / TEXTURE_SIZE;

	addVertex(vec2(0.0, 1.0), vec3(0.0, 0.0, 1.0), tx, ty);
	addVertex(vec2(0.0, 0.0), vec3(0.0, 1.0, 1.0), tx, ty);
	addVertex(vec2(1.0, 1.0), vec3(0.0, 0.0, 0.0), tx, ty);
	addVertex(vec2(1.0, 0.0), vec3(0.0, 1.0, 0.0), tx, ty);

    EndPrimitive();
}

void draw_right()
{
	v_color = vec4(0, 1, 1, 1);
	v_normal = vec3(1, 0, 0);

	float tx = v_texture[0][3] % TEXTURE_SIZE;
	float ty = v_texture[0][3] / TEXTURE_SIZE;

	addVertex(vec2(0.0, 1.0), vec3(1.0, 0.0, 0.0), tx, ty);
	addVertex(vec2(0.0, 0.0), vec3(1.0, 1.0, 0.0), tx, ty);
	addVertex(vec2(1.0, 1.0), vec3(1.0, 0.0, 1.0), tx, ty);
	addVertex(vec2(1.0, 0.0), vec3(1.0, 1.0, 1.0), tx, ty);

    EndPrimitive();
}

void draw_front()
{
	v_color = vec4(1, 0, 0, 1);
	v_normal = vec3(0, 0, -1);

	float tx = v_texture[0][4] % TEXTURE_SIZE;
	float ty = v_texture[0][4] / TEXTURE_SIZE;

	addVertex(vec2(0.0, 0.0), vec3(0.0, 1.0, 0.0), tx, ty);
	addVertex(vec2(1.0, 0.0), vec3(1.0, 1.0, 0.0), tx, ty);
	addVertex(vec2(0.0, 1.0), vec3(0.0, 0.0, 0.0), tx, ty);
	addVertex(vec2(1.0, 1.0), vec3(1.0, 0.0, 0.0), tx, ty);

    EndPrimitive();
}

void draw_back()
{
	v_color = vec4(1, 1, 0, 1);
	v_normal = vec3(0, 0, 1);

	float tx = v_texture[0][5] % TEXTURE_SIZE;
	float ty = v_texture[0][5] / TEXTURE_SIZE;

	addVertex(vec2(1.0, 1.0), vec3(0.0, 0.0, 1.0), tx, ty);
	addVertex(vec2(0.0, 1.0), vec3(1.0, 0.0, 1.0), tx, ty);
	addVertex(vec2(1.0, 0.0), vec3(0.0, 1.0, 1.0), tx, ty);
	addVertex(vec2(0.0, 0.0), vec3(1.0, 1.0, 1.0), tx, ty);

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
