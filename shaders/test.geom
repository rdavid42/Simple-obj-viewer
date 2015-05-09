#version 410

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in vec3 out_color1[];
in float out_anim[];
out vec3 out_color2;

void main()
{
	float		grey;

	if (out_anim[0] == 0.0f)
		out_color2 = vec3(out_color1[0].x, out_color1[0].y, out_color1[0].z);
	else
	{
		grey = (gl_in[0].gl_Position.x * gl_in[0].gl_Position.y * gl_in[0].gl_Position.z)
			- (gl_in[1].gl_Position.x * gl_in[1].gl_Position.y * gl_in[1].gl_Position.z)
			- (gl_in[2].gl_Position.x * gl_in[2].gl_Position.y * gl_in[2].gl_Position.z) / 42;
		if (grey < 0.2)
			grey = 0.2;
		if (grey <= 0.5 && grey >= 0.3)
			grey = 0.4;
		if (grey > 0.8)
			grey = 0.8;
		out_color2 = vec3(grey, grey, grey);
	}
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();
}
