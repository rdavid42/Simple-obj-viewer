/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:59:02 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:59:02 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "core.h"

static void			fill_vertices(t_object *o, char *line, int *j)
{
	static GLfloat const	grey_lim[3] = { 0.2f, 0.2f, 1.0f };
	static GLfloat			grey = 0.2f;

	sscanf(line, "v %f %f %f", &o->vertices[j[0]],
		&o->vertices[j[0] + 1], &o->vertices[j[0] + 2]);
	o->vertices[j[0] + 3] = grey;
	o->vertices[j[0] + 4] = grey;
	o->vertices[j[0] + 5] = grey;
	grey += grey_lim[1];
	if (grey >= grey_lim[2])
		grey = grey_lim[0];
	j[0] += 6;
}

static void			fill_indices(t_object *o, char *line, int *j)
{
	int				r;
	int				i[4];

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

static int			parse_object_data(char *file, int *file_size, t_object *o)
{
	int				index;
	char			*line;
	int				size;
	int				j[2];

	index = 0;
	line = NULL;
	j[0] = 0;
	j[1] = 0;
	while ((line = get_buffer_next_line(file, file_size,
										&index, &size)) != NULL)
	{
		if (size > 1)
		{
			if (!sncmp(line, "v ", 2))
				fill_vertices(o, line, j);
			else if (!sncmp(line, "f ", 2))
				fill_indices(o, line, j);
		}
		free(line);
		line = NULL;
	}
	return (1);
}

static void			count_object_data(char *file, int *file_size, t_object *o)
{
	int				index;
	char			*line;
	int				size;
	int				r;
	int				i[4];

	index = 0;
	line = NULL;
	while ((line = get_buffer_next_line(file, file_size, &index, &size)))
	{
		if (!sncmp(line, "v ", 2))
			o->vertices_size++;
		else if (!sncmp(line, "f ", 2))
		{
			r = sscanf(line, "f %d %d %d %d", &i[0], &i[1], &i[2], &i[3]);
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
	if (!alloc_object(o))
		return (0);
	parse_object_data(file, &file_size, o);
	free(file);
	return (1);
}
