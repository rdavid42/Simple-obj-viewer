#version 410

in vec3 out_color2;
out vec4 out_fragment;

void main()
{
	out_fragment = vec4(out_color2, 1.0);
}
