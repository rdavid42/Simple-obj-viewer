
#include <stdio.h>
#include <stdlib.h>
#include "core.h"

void				init_object(t_object *o)
{
	o->vertices_size = 0;
	o->quad_indices_size = 0;
	o->trig_indices_size = 0;
	o->vertices = NULL;
	o->quad_indices = NULL;
	o->trig_indices = NULL;
}

int					alloc_object(t_object *o)
{
	if (o->vertices_size > 0)
		if (!(o->vertices =
			(float *)malloc(sizeof(float) * o->vertices_size)))
			return (print_error("Failed to allocate vertices !\n", 0));
	if (o->quad_indices_size > 0)
		if (!(o->quad_indices =
			(int *)malloc(sizeof(int) * o->quad_indices_size)))
			return (print_error("Failed to allocate indices !\n", 0));
	if (o->trig_indices_size > 0)
		if (!(o->trig_indices =
			(int *)malloc(sizeof(int) * o->trig_indices_size)))
			return (print_error("Failed to allocate indices !\n", 0));
	return (1);
}

void				release_object(t_object *o)
{
	if (o->vertices != NULL)
		free(o->vertices);
	if (o->quad_indices != NULL)
		free(o->quad_indices);
	if (o->trig_indices != NULL)
		free(o->trig_indices);
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
	return (size + 1);
}

char				*get_buffer_next_line(char *file, int *offset)
{
	int const		size = get_buffer_next_line_size(file, offset);
	char			*line;
	int				i;

	if (size == 0)
		return (NULL);
	if (!(line = (char *)malloc(sizeof(char) * size + 1)))
		return (print_error_p("Failed to allocate memory !\n"));
	i = 0;
	while (file[*offset + i] != '\n' && file[*offset + i] != '\0')
	{
		line[i] = file[*offset + i];
		i++;
	}
	line[i] = '\0';
	*offset += size;
	return (line);
}

void				count_object_data(char *file, t_object *o)
{
	int				index;
	char			*line;
	int				r;
	int				t;

	index = 0;
	line = NULL;
	while ((line = get_buffer_next_line(file, &index)))
	{
		if (!sncmp(line, "v ", 2))
			o->vertices_size++;
		else if (!sncmp(line, "f ", 2))
		{
			r = sscanf(line + 1, " %d %d %d %d", &t, &t, &t, &t);
			if (r == 4)
				o->quad_indices_size++;
			if (r == 3)
				o->trig_indices_size++;
		}
		free(line);
		line = NULL;
	}
}

int					parse_object_data(char *file, t_object *o)
{
	int				index;
	char			*line;
	int				r;
	int				i[4];
	int				j[3];

	index = 0;
	line = NULL;
	j[0] = 0;
	j[1] = 0;
	j[2] = 0;
	while ((line = get_buffer_next_line(file, &index)))
	{
		if (!sncmp(line, "v ", 2))
		{
			r = sscanf(line + 1, " %f %f %f", &o->vertices[j[0]],
					&o->vertices[j[0] + 1], &o->vertices[j[0] + 2]);
			dprintf(2, "v %f, %f, %f\n", o->vertices[j[0]], o->vertices[j[0] + 1], o->vertices[j[0] + 2]);
			if (r != 3)
			{
				free(line);
				return (0);
			}
			j[0] += 3;
		}
		else if (!sncmp(line, "f ", 2))
		{
			r = sscanf(line + 1, " %d %d %d %d", &i[0], &i[1], &i[2], &i[3]);
			if (r == 4)
			{
				o->quad_indices[j[1] + 0] = i[0];
				o->quad_indices[j[1] + 1] = i[1];
				o->quad_indices[j[1] + 2] = i[2];
				o->quad_indices[j[1] + 3] = i[3];
				dprintf(2, "f %d %d %d %d\n", o->quad_indices[j[1] + 0], o->quad_indices[j[1] + 1], o->quad_indices[j[1] + 2], o->quad_indices[j[1] + 3]);
				j[1] += 4;
			}
			else if (r == 3)
			{
				o->trig_indices[j[2] + 0] = i[0];
				o->trig_indices[j[2] + 1] = i[1];
				o->trig_indices[j[2] + 2] = i[2];
				dprintf(2, "f %d %d %d\n", o->quad_indices[j[1] + 0], o->quad_indices[j[1] + 1], o->quad_indices[j[1] + 2]);
				j[2] += 3;
			}
		}
		free(line);
		line = NULL;
	}
	return (1);
}

int					parse_object(char const *filename, t_object *o)
{
	char			*file;

	init_object(o);
	if (!(file = read_file(filename)))
		return (0);
	count_object_data(file, o);
	dprintf(2, "vertices: %d, quads: %d, trigs: %d\n", o->vertices_size, o->quad_indices_size, o->trig_indices_size);
	if (!alloc_object(o))
		return (0);
	parse_object_data(file, o);
	free(file);
	return (1);
}
