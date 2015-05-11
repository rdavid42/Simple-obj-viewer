#version 410

#define M_PI 3.1415926535897932384626433832795

// varying -> out
// attribute -> in

// uniform => global for all vertices in a draw call

mat4		rotation_matrix(vec3 axis, float angle)
{
	float		s = sin(angle);
	float		c = cos(angle);
	float		oc = 1.0 - c;

	axis = normalize(axis);
	return (mat4(oc * axis.x * axis.x + c,			oc * axis.x * axis.y - axis.z * s,	oc * axis.z * axis.x + axis.y * s,	0.0,
				 oc * axis.x * axis.y + axis.z * s,	oc * axis.y * axis.y + c,			oc * axis.y * axis.z - axis.x * s,	0.0,
				 oc * axis.z * axis.x - axis.y * s,	oc * axis.y * axis.z + axis.x * s,	oc * axis.z * axis.z + c,			0.0,
				 0.0,								0.0,								0.0,								1.0));
}

mat4		translation_matrix(vec3 t)
{
	t = normalize(t);

	return (mat4(1.0, 0.0, 0.0, 0.0,
				 0.0, 1.0, 0.0, 0.0,
				 0.0, 0.0, 1.0, 0.0,
				 t.x, t.y, t.z, 1.0));
}

float		deg_to_rad(float x)
{
	return (x / 180.0 * M_PI);
}

uniform mat4 view_matrix, proj_matrix;
uniform float y_deg;
uniform float anim;
uniform float vert_tex_enabled;
uniform float tex_scale;
uniform vec3 rot;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 in_color;

out vec3 out_color1;
out float out_anim;
out vec2 geom_tex_coord;
out float geom_tex_enabled;

void main()
{
	geom_tex_enabled = vert_tex_enabled;
	geom_tex_coord = vec2(position.z * tex_scale, position.y * tex_scale);
	gl_Position = proj_matrix * view_matrix
				* rotation_matrix(vec3(rot.x, rot.y, rot.z), deg_to_rad(y_deg))
				* translation_matrix(vec3(0.0, 0.0, -1.0))
				* vec4(position, 1.0);
	out_color1 = in_color;
	out_anim = anim;
}
