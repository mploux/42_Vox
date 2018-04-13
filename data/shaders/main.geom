#version 150 core

layout(points) in;
layout(line_strip, max_vertices = 2) out;

in vec3 v_position;

void main()
{
    gl_Position = v_position + vec4(-0.1, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = v_position + vec4(0.1, 0.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}