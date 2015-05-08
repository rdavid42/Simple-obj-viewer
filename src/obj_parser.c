
#include <stdio.h>
#include <stdlib.h>
#include "core.h"

void				init_object(t_object *o)
{
	o->vertices_size = 0;
	o->indices_size = 0;
	o->vertices = NULL;
	o->indices = NULL;
}

int					alloc_object(t_object *o)
{
	if (o->vertices_size > 0)
	{
		if (!(o->vertices =
			(GLfloat *)malloc(sizeof(GLfloat) * o->vertices_size * 3)))
			return (print_error("Failed to allocate vertices !\n", 0));
	}
	if (o->indices_size > 0)
	{
		if (!(o->indices =
			(GLushort *)malloc(sizeof(GLushort) * o->indices_size * 3)))
			return (print_error("Failed to allocate indices !\n", 0));
	}
	return (1);
}

void				release_object(t_object *o)
{
	if (o->vertices != NULL)
		free(o->vertices);
	if (o->indices != NULL)
		free(o->indices);
}

int					get_buffer_next_line_size(char *file, int *offset)
{
	int				size;

	size = 0;
	while (file[*offset + size] != '\n')
	{
		if (!file[*offset + size])
			return (size);
		size++;
	}
	return (size);
}

char				*get_buffer_next_line(char *file, int *file_size, int *offset)
{
	int				size;
	char			*line;
	int				i;

	if (offset >= file_size)
		return (NULL);
	if (!(size = get_buffer_next_line_size(file, offset)))
		return (NULL);
	if (!(line = (char *)malloc(sizeof(char) * size + 1)))
		return (print_error_p("Failed to allocate memory !\n"));
	i = 0;
	while (file[*offset + i] != '\n' && file[*offset + i] != '\0')
	{
		line[i] = file[*offset + i];
		i++;
	}
	line[size] = '\0';
	*offset += size + 1;
	return (line);
}

int					parse_object_data(char *file, int *file_size, t_object *o)
{
	int				index;
	char			*line;
	int				r;
	int				i[4];
	int				j[2];

	(void)o;
	index = 0;
	line = NULL;
	j[0] = 0;
	j[1] = 0;
	while ((line = get_buffer_next_line(file, file_size, &index)) != NULL)
	{
		if (!sncmp(line, "v ", 2))
		{
			r = sscanf(line, "v %f %f %f", &o->vertices[j[0]],
					&o->vertices[j[0] + 1], &o->vertices[j[0] + 2]);
			j[0] += 3;
		}
		else if (!sncmp(line, "f ", 2))
		{
			r = sscanf(line, "f %d %d %d %d", &i[0], &i[1], &i[2], &i[3]);
			if (r == 4)
			{
				o->indices[j[1] + 0] = i[0] - 1;
				o->indices[j[1] + 1] = i[1] - 1;
				o->indices[j[1] + 2] = i[2] - 1;
				o->indices[j[1] + 3] = i[0] - 1;
				o->indices[j[1] + 4] = i[2] - 1;
				o->indices[j[1] + 5] = i[3] - 1;
				j[1] += 6;
			}
			else if (r == 3)
			{
				o->indices[j[1] + 0] = i[0] - 1;
				o->indices[j[1] + 1] = i[1] - 1;
				o->indices[j[1] + 2] = i[2] - 1;
				j[1] += 3;
			}
		}
		free(line);
		line = NULL;
	}
	return (1);
}

void				count_object_data(char *file, int *file_size, t_object *o)
{
	int				index;
	char			*line;
	int				r;
	int				t;

	index = 0;
	line = NULL;
	while ((line = get_buffer_next_line(file, file_size, &index)))
	{
		if (!sncmp(line, "v ", 2))
			o->vertices_size++;
		else if (!sncmp(line, "f ", 2))
		{
			r = sscanf(line, "f %d %d %d %d", &t, &t, &t, &t);
			if (r == 4)
				o->indices_size += 2;
			if (r == 3)
				o->indices_size++;
		}
		free(line);
		line = NULL;
	}
}

int					parse_object(char const *filename, t_object *o)
{
	int				file_size;
	char			*file;

	init_object(o);
	if (!(file = read_file(filename)))
		return (0);
	file_size = slen(file);
	count_object_data(file, &file_size, o);
	dprintf(2, "vertices: %d, indices: %d\n", o->vertices_size, o->indices_size);
	if (!alloc_object(o))
		return (0);
	parse_object_data(file, &file_size, o);
	free(file);
	return (1);
}
