#version 400 core

out vec4 out_color;

in vec4 g_color;

void main()
{
	out_color = g_color;
}
