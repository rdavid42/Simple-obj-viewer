
#include <stdlib.h>
#include <string.h>
#include "core.h"

int					compile_shader(GLuint shader, char const *filename)
{
	GLint			logsize;
	GLint			state;
	char			*compilelog;

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
	return (1);
}

GLuint				load_shader(GLenum type, char const *filename)
{
	GLuint			shader;
	char			*source;

	shader = glCreateShader(type);
	if (shader == 0)
		return (print_error("Could not create shader !", 0));
	if (!(source = read_file(filename)))
		return (print_error("Could not read file !\n", 0));
	glShaderSource(shader, 1, (char const **)&source, 0);
	if (!compile_shader(shader, filename))
		return (0);
	free(source);
	return (shader);
}
