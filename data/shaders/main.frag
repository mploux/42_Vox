#version 400 core

out vec4 out_color;

uniform vec3 cameraPosition;
uniform sampler2D tex;

in vec2 v_texture;
in vec3 v_normal;
in vec3 frag_pos;

void main()
{
	vec3 lightDirection = normalize(-frag_pos - cameraPosition);
	float lightIntensity = dot(lightDirection, v_normal) * 0.5 + 0.5;

	vec4 texture_color = texture(tex, v_texture);

	if (texture_color.a < 0.2)
		discard;

	out_color = vec4(texture_color.xyz * vec3(1.3, 1.3, 1.0) * lightIntensity, 1.0) * texture_color.a;
}
