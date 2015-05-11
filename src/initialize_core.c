
#include "core.h"

int			initialize_core(t_core *c)
{
	if (!(c->mlx_init = mlx_init()))
		return (print_error("Could not initialize minilibx !\n", 0));
	create_window(c);
	if (!init_shaders(c))
		return (0);
	c->texture = load_texture("resources/kitten.bmp");
	get_locations(c);
	c->rotations = create_vec(0.0f, 1.0f, 0.0f);
	c->tex_scale = 1.0f;
	c->anim = 0.0f;
	c->translate = create_vec(0.0f, 0.0f, 0.0f);
	c->y_deg = 0.0f;
	c->tex_enabled = 0.0f;
	c->cam_pos = create_vec(5.0f, 0.0f, 0.0f);
	c->cam_look_at = create_vec(0.0f, 0.0f, 0.0f);
	create_buffers(c);
	build_projection_matrix(c, 53.13f, 1.0f, 30.0f);
	check_gl_error(__LINE__);
	return (1);
}
