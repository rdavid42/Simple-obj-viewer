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

void		check_gl_error(int code)
{
	GLenum		err;

	err = glGetError();
	if (err != GL_NO_ERROR)
	{
		if (err == GL_INVALID_ENUM)
			dprintf(2, "(%d) Invalid enum !\n", code);
		else if (err == GL_INVALID_VALUE)
			dprintf(2, "(%d) Invalid value !\n", code);
		else if (err == GL_INVALID_OPERATION)
			dprintf(2, "(%d) Invalid operation !\n", code);
		else if (err == GL_INVALID_FRAMEBUFFER_OPERATION)
			dprintf(2, "(%d) Invalid framebuffer operation !\n", code);
		else if (err == GL_OUT_OF_MEMORY)
			dprintf(2, "(%d) Out of memory !\n", code);
	}
}

int			create_image(t_window *w, t_image *img)
{
	img->data = mlx_new_image(w->mlx_init, w->width, w->height);
	get_image_data(img);
	return (1);
}

int			create_window(t_core *core)
{
	t_window				* const w = &core->window;

	w->init = mlx_new_opengl_window(core->mlx_init, WW, WH, "Scop");
	mlx_opengl_window_set_context(w->init);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
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

int			loop_hook(t_core *c)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(c->program);
	check_gl_error(__LINE__);
	glEnableVertexAttribArray(0);
	check_gl_error(__LINE__);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	check_gl_error(__LINE__);
	glDrawElements(GL_TRIANGLES, c->otest.indices_size, GL_UNSIGNED_SHORT, 0);
	check_gl_error(__LINE__);
	mlx_opengl_swap_buffers(c->window.init);
	return (1);
}

int			initialize_core(t_core *core)
{
	if (!(core->mlx_init = mlx_init()))
		return (print_error("Could not initialize minilibx !\n", 0));
	create_window(core);
	if (!init_shaders(core))
		return (0);
/*	int			i;

	i = 0;
	while (i < core->otest.vertices_size * 3)
	{
		dprintf(2, "v: %f, %f, %f\n", core->otest.vertices[i], core->otest.vertices[i + 1], core->otest.vertices[i + 2]);
		i += 3;
	}
	i = 0;
	while (i < core->otest.indices_size * 3)
	{
		dprintf(2, "f: %d, %d, %d\n", core->otest.indices[i], core->otest.indices[i + 1], core->otest.indices[i + 2]);
		i += 3;
	}*/
	glGenVertexArrays(1, &core->otest.vao_id);
	glBindVertexArray(core->otest.vao_id);
	// vertices
	glGenBuffers(1, &core->otest.vertex_vbo_id);
	check_gl_error(__LINE__);
	glBindBuffer(GL_ARRAY_BUFFER, core->otest.vertex_vbo_id);
	check_gl_error(__LINE__);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * core->otest.vertices_size * 3, core->otest.vertices, GL_STATIC_DRAW);
	check_gl_error(__LINE__);
	// indices
	glGenBuffers(1, &core->otest.indice_vbo_id);
	check_gl_error(__LINE__);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, core->otest.indice_vbo_id);
	check_gl_error(__LINE__);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * core->otest.indices_size * 3, core->otest.indices, GL_STATIC_DRAW);
	check_gl_error(__LINE__);
	return (1);
}

int			main(int argc, char **argv)
{
	t_core			core;

	if (!parse_object("resources/42.obj", &core.otest))
		return (print_error("Failed to parse object !\n", 0));
	if (!initialize_core(&core))
		return (0);
	mlx_loop(core.mlx_init);
	(void)argc;
	(void)argv;
	return (0);
}
