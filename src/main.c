/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 17:26:44 by rdavid            #+#    #+#             */
/*   Updated: 2015/04/04 17:26:44 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "core.h"

void		get_image_data(t_image *img)
{
	img->p_data = mlx_get_data_addr(img->data, &img->bpp, &img->sizeline, &img->endian);
}

int			expose_hook(t_window *window)
{
	if (window)
	{
		// mlx_put_image_to_window(window->mlx_init, window->init,
								// window->img.data, 0, 0);
	}
	return (1);
}

void		update_image(t_window *window)
{
	(void)window;
	// mlx_put_image_to_window(window->mlx_init, window->init,
							// window->img.data, 0, 0);
}

int			key_hook(unsigned int key, t_window *window)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_DOWN)
	{
	}
	else if (key == K_UP)
	{
	}
	(void)window;
	return (1);
}

int			mouse_hook(int button, int x, int y, t_window *window)
{
	(void)button;
	(void)x;
	(void)y;
	(void)window;
	return (1);
}

int			mouse_event(int x, int y, t_window *window)
{
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > window->width)
		x = window->width;
	if (y > window->height)
		y = window->height;
	window->mx = x;
	window->my = y;
	return (1);
}

int			loop_hook(t_core *c)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(c->program);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, c->vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	mlx_opengl_swap_buffers(c->window.init);
	return (1);
}

int			create_image(t_window *w, t_image *img)
{
	img->data = mlx_new_image(w->mlx_init, w->width, w->height);
	get_image_data(img);
	return (1);
}

void		init_vertex_data(t_core *c)
{
	c->vertex_data[0] = -1.0f;
	c->vertex_data[1] = -1.0f;
	c->vertex_data[2] = 0.0f;
	c->vertex_data[3] = 1.0f;
	c->vertex_data[4] = -1.0f;
	c->vertex_data[5] = 0.0f;
	c->vertex_data[6] = 0.0f;
	c->vertex_data[7] = 1.0f;
	c->vertex_data[8] = 0.0f;
}

int			create_window(t_core *core)
{
	t_window				* const w = &core->window;


	w->init = mlx_new_opengl_window(core->mlx_init, WW, WH, "Scop");
	mlx_opengl_window_set_context(w->init);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	w->width = WW;
	w->height = WH;
	mlx_expose_hook(w->init, expose_hook, w);
	mlx_key_hook(w->init, key_hook, w);
	mlx_hook(w->init, MOTION, MOTION_MASK, mouse_event, w);
	mlx_mouse_hook(w->init, mouse_hook, w);
	mlx_loop_hook(core->mlx_init, loop_hook, core);
	w->mx = 0;
	w->my = 0;
	return (1);
}

int			initialize_core(t_core *core)
{
	if (!(core->mlx_init = mlx_init()))
		return (print_error("Could not initialize minilibx !\n", 0));
	init_vertex_data(core);
	create_window(core);
	glGenVertexArrays(1, &core->vao_id);
	glBindVertexArray(core->vao_id);
	glGenBuffers(1, &core->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, core->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(core->vertex_data), core->vertex_data, GL_STATIC_DRAW);
	if (!init_shaders(core))
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_core			core;

	if (!initialize_core(&core))
		return (0);
	mlx_loop(core.mlx_init);
	(void)argc;
	(void)argv;
	return (0);
}
