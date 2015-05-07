#version 410

in vec3 out_color;
out vec4 out_fragment;

void main()
{
	out_fragment = vec4(out_color, 1.0);
}
