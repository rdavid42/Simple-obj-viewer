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

#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "core.h"
#include "bmp_loader.h"

void		cross_product(t_vec *a, t_vec *b, t_vec *r)
{
	r->x = a->y * b->z - b->y * a->z;
	r->y = a->z * b->x - b->z * a->x;
	r->z = a->x * b->y - b->x * a->y;
}

void		normalize(t_vec *a)
{
	float const		magnitude = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);

	a->x /= magnitude;
	a->y /= magnitude;
	a->z /= magnitude;
}

void		set_identity_matrix(float *mat, int size)
{
	int				i;
	int const		s2 = size * size;

	i = 0;
	while (i < s2)
	{
		mat[i] = 0.0f;
		i++;
	}
	i = 0;
	while (i < size)
	{
		mat[i + i * size] = 1.0f;
		i++;
	}
}

void		multiply_matrix(float *a, float *b)
{
	float	res[16];
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res[j * 4 + i] = 0.0f;
			k = 0;
			while (k < 4)
			{
				res[j * 4 + i] += a[k * 4 + i] * b[j * 4 + k];
				++k;
			}
			++j;
		}
		++i;
	}
	memcpy(a, res, 16 * sizeof(float));
}

void		set_translation_matrix(float *mat, float x, float y, float z)
{
	set_identity_matrix(mat, 4);
	mat[12] = x;
	mat[13] = y;
	mat[14] = z;
}

void		build_projection_matrix(t_core *c, float fov, float near_p, float far_p)
{
	float const		f = 1.0f / tan (fov * (M_PI / 360.0));
	float const		ratio = (1.0f * c->window.width) / c->window.height;

	set_identity_matrix(c->proj_matrix, 4);
	c->proj_matrix[0] = f / ratio;
	c->proj_matrix[1 * 4 + 1] = f;
	c->proj_matrix[2 * 4 + 2] = (far_p + near_p) / (near_p - far_p);
	c->proj_matrix[3 * 4 + 2] = (2.0f * far_p * near_p) / (near_p - far_p);
	c->proj_matrix[2 * 4 + 3] = -1.0f;
	c->proj_matrix[3 * 4 + 3] = 0.0f;
}

t_vec		create_vec(float x, float y, float z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

void		set_view_matrix(float *view_matrix, t_vec *dir,
							t_vec *right, t_vec *up)
{
	view_matrix[0] = right->x;
	view_matrix[4] = right->y;
	view_matrix[8] = right->z;
	view_matrix[12] = 0.0f;
	view_matrix[1] = up->x;
	view_matrix[5] = up->y;
	view_matrix[9] = up->z;
	view_matrix[13] = 0.0f;
	view_matrix[2] = -dir->x;
	view_matrix[6] = -dir->y;
	view_matrix[10] = -dir->z;
	view_matrix[14] = 0.0f;
	view_matrix[3] = 0.0f;
	view_matrix[7] = 0.0f;
	view_matrix[11] = 0.0f;
	view_matrix[15] = 1.0f;
}

void		set_camera(float *view_matrix, t_vec pos, t_vec look_at)
{
	t_vec	dir;
	t_vec	right;
	t_vec	up;
	float	aux[16];

	up = create_vec(0.0f, 1.0f, 0.0f);
	dir = create_vec(look_at.x - pos.x, look_at.y - pos.y, look_at.z - pos.z);
	normalize(&dir);
	cross_product(&dir, &up, &right);
	normalize(&right);
	cross_product(&right, &dir, &up);
	normalize(&up);
	set_view_matrix(view_matrix, &dir, &right, &up);
	set_translation_matrix(aux, -pos.x, -pos.y, -pos.z);
	multiply_matrix(view_matrix, aux);
}

void		get_image_data(t_image *img)
{
	img->p_data = mlx_get_data_addr(img->data, &img->bpp, &img->sizeline, &img->endian);
}

int			expose_hook(t_core *core)
{
	(void)core;
	// mlx_put_image_to_window(window->mlx_init, window->init,
							// window->img.data, 0, 0);
	return (1);
}

void		update_image(t_window *window)
{
	(void)window;
	// mlx_put_image_to_window(window->mlx_init, window->init,
							// window->img.data, 0, 0);
}

int			key_hook(unsigned int key, t_core *c)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_A)
		c->anim = !c->anim;
	return (1);
}

int			key_hook_repeat(unsigned int key, t_core *c)
{
	if (key == K_DOWN)
		c->translate.y += TRANSLATE_SPEED;
	else if (key == K_UP)
		c->translate.y -= TRANSLATE_SPEED;
	else if (key == K_LEFT)
		c->translate.z -= TRANSLATE_SPEED;
	else if (key == K_RIGHT)
		c->translate.z += TRANSLATE_SPEED;
	else if (key == K_KPLUS)
		c->translate.x -= TRANSLATE_SPEED;
	else if (key == K_KMIN)
		c->translate.x += TRANSLATE_SPEED;
	return (1);
}

int			mouse_hook(int button, int x, int y, t_core *core)
{
	(void)button;
	(void)x;
	(void)y;
	(void)core;
	return (1);
}

int			mouse_event(int x, int y, t_core *core)
{
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > core->window.width)
		x = core->window.width;
	if (y > core->window.height)
		y = core->window.height;
	core->window.mx = x;
	core->window.my = y;
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

int			loop_hook(t_core *c)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	c->cam_pos = create_vec(5.0f + c->translate.x, c->translate.y, c->translate.z);
	c->cam_look_at = create_vec(c->translate.x, c->translate.y, c->translate.z);
	set_camera(c->view_matrix, c->cam_pos, c->cam_look_at);
	glUseProgram(c->program);
	glUniformMatrix4fv(c->proj_loc, 1, GL_FALSE, c->proj_matrix);
	glUniformMatrix4fv(c->view_loc, 1, GL_FALSE, c->view_matrix);
	glUniform1f(c->y_deg_loc, c->y_deg);
	glUniform1f(c->anim_loc, c->anim);
	glDrawElements(GL_TRIANGLES, c->otest.indices_size * 3, GL_UNSIGNED_SHORT, 0);
	check_gl_error(__LINE__);
	c->y_deg++;
	if (c->y_deg == 360)
		c->y_deg = 0;
	mlx_opengl_swap_buffers(c->window.init);
	return (1);
}

void		get_locations(t_core *c)
{
	c->position_loc = glGetAttribLocation(c->program, "position");
	c->color_loc = glGetAttribLocation(c->program, "in_color");
	c->tex_coord_loc = glGetAttribLocation(c->program, "vert_tex_coord");

	c->y_deg_loc = glGetUniformLocation(c->program, "y_deg");
	c->anim_loc = glGetUniformLocation(c->program, "anim");
	c->proj_loc = glGetUniformLocation(c->program, "proj_matrix");
	c->view_loc = glGetUniformLocation(c->program, "view_matrix");
	c->texture_loc = glGetUniformLocation(c->program, "texture_unit");
}

void		create_buffers(t_core *c)
{
	glGenVertexArrays(1, &c->otest.vao_id);
	glBindVertexArray(c->otest.vao_id);
	glGenBuffers(4, &c->otest.vbo_ids[0]);
	glBindBuffer(GL_ARRAY_BUFFER, c->otest.vbo_ids[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * c->otest.vertices_size * 3, c->otest.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(c->position_loc);
	glVertexAttribPointer(c->position_loc, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, c->otest.vbo_ids[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * c->otest.indices_size * 3, c->otest.colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(c->color_loc);
	glVertexAttribPointer(c->color_loc, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, c->otest.vbo_ids[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * c->otest.indices_size * 6, c->otest.texture_coord, GL_STATIC_DRAW);
	glEnableVertexAttribArray(c->tex_coord_loc);
	glVertexAttribPointer(c->tex_coord_loc, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c->otest.vbo_ids[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * c->otest.indices_size * 3, c->otest.indices, GL_STATIC_DRAW);
	check_gl_error(__LINE__);
}

GLuint		load_texture(char const *filename)
{
	GLuint				texture;
	unsigned char		*img;
	t_bmp				bmp;

	img = load_bmp(filename, &bmp);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.width, bmp.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	return (texture);
}

int			initialize_core(t_core *c)
{
	if (!(c->mlx_init = mlx_init()))
		return (print_error("Could not initialize minilibx !\n", 0));
	create_window(c);
	if (!init_shaders(c))
		return (0);
	c->texture = load_texture("resources/kitten.bmp");
	get_locations(c);
	c->anim = 0.0f;
	c->translate = create_vec(0.0f, 0.0f, 0.0f);
	c->y_deg = 0;
	c->cam_pos = create_vec(5.0f, 0.0f, 0.0f);
	c->cam_look_at = create_vec(0.0f, 0.0f, 0.0f);
	create_buffers(c);
	build_projection_matrix(c, 53.13f, 1.0f, 30.0f);
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
