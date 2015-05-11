#version 410

uniform sampler2D tex;

in vec3 out_color2;
in vec2 frag_tex_coord;
out vec4 out_fragment;

void main()
{
	out_fragment = texture(tex, frag_tex_coord);//vec4(out_color2, 1.0);
	// out_fragment = vec4(out_color2, 1.0);
}
