
#include <stdlib.h>
#include <string.h>
#include "core.h"

static int			load_shaders(t_core *c)
{
	if (!(c->vertex_shader = load_shader(GL_VERTEX_SHADER, "./shaders/test.vert")))
		return (print_error("Could not load vertex shader !\n", 0));
	if (!(c->fragment_shader = load_shader(GL_FRAGMENT_SHADER, "./shaders/test.frag")))
		return (print_error("Could not load fragment shader !\n", 0));
	if (!(c->geometry_shader = load_shader(GL_GEOMETRY_SHADER, "./shaders/test.geom")))
		return (print_error("Could not load geometry shader !\n", 0));
	return (1);
}

static void			attach_shaders(t_core *c)
{
	glAttachShader(c->program, c->vertex_shader);
	glAttachShader(c->program, c->fragment_shader);
	glAttachShader(c->program, c->geometry_shader);
}

static int			link_program(t_core *c)
{
	GLint			logsize;
	GLint			state;
	char			*link_log;

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
	return (1);
}

static void			delete_shaders(t_core *c)
{
	glDeleteShader(c->vertex_shader);
	glDeleteShader(c->fragment_shader);
}

int					init_shaders(t_core *c)
{
	if (!load_shaders(c))
		return (0);
	if (!(c->program = glCreateProgram()))
		return (print_error("Failed to create program !", 0));
	attach_shaders(c);
	glBindFragDataLocation(c->program, 0, "out_fragment");
	if (!link_program(c))
		return (0);
	delete_shaders(c);
	return (1);
}
