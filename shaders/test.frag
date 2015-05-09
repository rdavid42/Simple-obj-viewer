#version 410

uniform sampler2D texture_unit;
in vec3 out_color2;
in vec2 frag_tex_coord;
out vec4 out_fragment;

void main()
{
	out_fragment = texture(texture_unit, frag_tex_coord);
	// out_fragment = vec4(out_color2, 1.0);
}
