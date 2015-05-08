#version 410

// varying -> out
// attribute -> in

// uniform => global for all vertices in a draw call

uniform mat4 view_matrix, proj_matrix;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 in_color;

out vec3 out_color;

void main()
{
	gl_Position = proj_matrix * view_matrix * vec4(position, 1.0);
	out_color = in_color;
}
