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

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "core.h"

int			print_error(char const *msg, int const code)
{
	return (code + 0 * write(2, msg, slen(msg)));
}

void		*print_error_p(char const *msg)
{
	int		ret;

	ret = write(2, msg, slen(msg));
	(void)ret;
	return (NULL);
}

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

int			file_size(char const *filename)
{
	int		fd;
	int		ret;
	int		count;
	char	buf[4096];

	if ((fd = open(filename, O_RDONLY, 0644)) == -1)
		return (print_error("Could not open file !\n", -1));
	count = 0;
	while ((ret = read(fd, buf, 4096)) != 0)
	{
		if (ret == -1)
		{
			close(fd);
			return (print_error("Could not read file !\n", -1));
		}
		count += ret;
	}
	close(fd);
	return (count);
}

char		*read_file(char const *filename)
{
	int				size;
	int				fd;
	int				i[2];
	char			buf;
	char			*file;

	if ((size = file_size(filename)) == -1)
		return (print_error_p("Could not get file size !\n"));
	if (!(file = (char *)malloc(sizeof(char) * size + 1)))
		return (print_error_p("Could not allocate memory !\n"));
	if ((fd = open(filename, O_RDONLY, 0644)) == -1)
		return (print_error_p("Could not open file !\n"));
	i[1] = 0;
	while ((i[0] = read(fd, &buf, 1)) != 0)
	{
		if (i[0] == -1)
		{
			close(fd);
			return (print_error_p("Could not read file !\n"));
		}
		file[i[1]] = buf;
		i[1]++;
	}
	file[i[1]] = '\0';
	return (file);
}

GLuint		load_shader(GLenum type, char const *filename)
{
	GLuint			shader;
	GLint			state;
	GLint			logsize;
	char			*compilelog;
	char			*source;

	shader = glCreateShader(type);
	if (shader == 0)
		return (print_error("Could not create shader !", 0));
	if (!(source = read_file(filename)))
		return (print_error("Could not read file !\n", 0));
	glShaderSource(shader, 1, (char const **)&source, 0);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &state);
	if (state != GL_TRUE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
		if (!(compilelog = (char *)malloc(sizeof(char) * logsize + 1)))
			return (0);
		memset(compilelog, '\0', logsize + 1);
		glGetShaderInfoLog(shader, logsize, &logsize, compilelog);
		print_error("Could not compile shader `", 0);
		print_error(filename, 0);
		print_error("`: \n", 0);
		print_error(compilelog, 0);
		free(compilelog);
		return (0);
	}
	return (shader);
}

int			init_shaders(t_core *c)
{
	GLint			state;
	GLint			logsize;
	char			*link_log;

	if (!(c->vertex_shader = load_shader(GL_VERTEX_SHADER, "./shaders/test.vert")))
		return (print_error("Could not load vertex shader !\n", 0));
	if (!(c->fragment_shader = load_shader(GL_FRAGMENT_SHADER, "./shaders/test.frag")))
		return (print_error("Could not load fragment shader !\n", 0));
	if (!(c->program = create_program()))
		return (print_error("Could not create program !\n", 0));
	glAttachShader(c->program, c->vertex_shader);
	glAttachShader(c->program, c->fragment_shader);
	glLinkProgram(c->program);
	glGetProgramiv(c->program, GL_LINK_STATUS, &state);
	if (state != GL_TRUE)
	{
		glGetProgramiv(c->program, GL_INFO_LOG_LENGTH, &logsize);
		if (!(link_log = (char *)malloc(sizeof(char) * logsize + 1)))
			return (print_error("Could not allocate memory !\n", 0));
		memset(link_log, '\0', logsize + 1);
		glGetProgramInfoLog(c->program, logsize, &logsize, link_log);
		print_error("Could not link program !\n", 0);
		print_error(link_log, 0);
		return (0);
	}
	glDeleteShader(c->vertex_shader);
	glDeleteShader(c->fragment_shader);
	return (1);
}

GLuint		create_program(void)
{
	GLuint		program;

	if (!(program = glCreateProgram()))
		return (print_error("Failed to create program !", 0));
	return (program);
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
	(void)c;
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
