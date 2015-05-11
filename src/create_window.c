
#include "core.h"

int			create_window(t_core *core)
{
	t_window				* const w = &core->window;

	w->init = mlx_new_opengl_window(core->mlx_init, WW, WH, "Scop");
	mlx_opengl_window_set_context(w->init);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	w->width = WW;
	w->height = WH;
	mlx_expose_hook(w->init, expose_hook, core);
	mlx_key_hook(w->init, key_hook, core);
	mlx_hook(w->init, 2, (1L << 0), key_hook_repeat, core);
	mlx_hook(w->init, MOTION, MOTION_MASK, mouse_event, core);
	mlx_mouse_hook(w->init, mouse_hook, core);
	mlx_loop_hook(core->mlx_init, loop_hook, core);
	w->mx = 0;
	w->my = 0;
	return (1);
}
