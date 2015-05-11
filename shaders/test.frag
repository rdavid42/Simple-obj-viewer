#version 410

uniform sampler2D tex;

in vec3 out_color2;
in vec2 frag_tex_coord;
in float frag_tex_enabled;
out vec4 out_fragment;

void main()
{
	out_fragment = frag_tex_enabled * texture(tex, frag_tex_coord);
	if (frag_tex_enabled == 0.0f)
		out_fragment = vec4(out_color2, 1.0);
}
