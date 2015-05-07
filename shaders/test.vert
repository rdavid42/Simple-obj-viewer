#version 410

// varying -> out
// attribute -> in

// uniform => global for all vertices in a draw call

uniform mat4 view_matrix, proj_matrix;

in vec4 position;
in vec3 in_color;

out vec3 out_color;

void main()
{
	gl_Position = proj_matrix * view_matrix * position;
	out_color = in_color;
}
