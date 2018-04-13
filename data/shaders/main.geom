#version 400 core
#extension GL_EXT_gpu_shader4 : enable

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

uniform mat4 projectionMatrix;

in vec4 v_trs[];
in int v_faces[];
out vec4 g_color;

void draw_front()
{
	g_color = vec4(1, 0, 0, 1);

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 1.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 1.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 0.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}

void draw_back()
{
	g_color = vec4(1, 1, 0, 1);

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 0.0, 1.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 0.0, 1.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 1.0, 1.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 1.0, 1.0, 0.0);
    EmitVertex();

    EndPrimitive();
}

void draw_left()
{
	g_color = vec4(1, 1, 0, 1);

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 0.0, 1.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 1.0, 1.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 1.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}

void draw_right()
{
	g_color = vec4(0, 1, 1, 1);

    gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 1.0, 0.0, 0.0);
    EmitVertex();

	gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 0.0, 1.0, 0.0);
	EmitVertex();

	gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 1.0, 1.0, 0.0);
	EmitVertex();

    EndPrimitive();
}

void draw_bottom()
{
	g_color = vec4(0, 0, 1, 1);

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 0.0, 1.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 0.0, 1.0, 0.0);
    EmitVertex();

    EndPrimitive();
}

void draw_top()
{
	g_color = vec4(1, 0, 1, 1);

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 1.0, 1.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 1.0, 1.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(0.0, 1.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = v_trs[0] + projectionMatrix * vec4(1.0, 1.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}

void main()
{
	if (v_faces[0] & (1 << 0)) draw_top();
	if (v_faces[0] & (1 << 1)) draw_bottom();
	if (v_faces[0] & (1 << 2)) draw_left();
	if (v_faces[0] & (1 << 3)) draw_right();
	if (v_faces[0] & (1 << 4)) draw_front();
	if (v_faces[0] & (1 << 5)) draw_back();
}
