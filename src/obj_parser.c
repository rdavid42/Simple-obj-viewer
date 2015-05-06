
#include <stdio.h>
#include <stdlib.h>
#include "core.h"

int					count_obj_data(char const *filename, t_mesh *m)
{
	char			n[256];
	FILE			*f;
	int				r;

	if (!(f = fopen(filename, "r")))
		return (0);
	while ((r = fscanf(f, "%s", n)) != EOF)
	{
		if (!sncmp(n, "v ", 2))
			m->vs++;
		else if (!sncmp(n, "f ", 2))
			m->fs++;
	}
	if (fclose(f) == EOF)
		return (print_error("Failed to close file !\n", 0));
}

void				init_mesh(t_mesh *m)
{
	m->vs = 0;
	m->vts = 0;
	m->fs = 0;
	m->v = NULL;
	m->vt = NULL;
	m->f = NULL;
}

int					alloc_mesh(t_mesh *m)
{
	if (m->vs > 0)
		if (!(m->v = (float *)malloc(sizeof(float) * m->vs)))
			return (print_error("Failed to allocate memory !\n", 0));
	if (m->vts > 0)
		if (!(m->vt = (float *)malloc(sizeof(float) * m->vts)))
			return (print_error("Failed to allocate memory !\n", 0));
	if (m->fs > 0)
		if (!(m->f = (float *)malloc(sizeof(float) * m->fs)))
			return (print_error("Failed to allocate memory !\n", 0));
	return (1);
}

int					parse_obj(char const *filename, t_mesh *m)
{
	char			n[256];
	FILE			*f;
	int				r;

	init_mesh(m);
	if (!count_obj_data(filename, m))
		return (0);
	dprintf(2, "vs: %d, vts: %d, fs: %d\n", m->vs, m->vts, m->fs);
	if (!alloc_mesh(m))
		return (0);
/*	if (!(f = fopen(filename, "r")))
		return (0);
	while ((r = fscanf(f, "%s", n)) != EOF)
	{
		if (!sncmp(n, "v", 1))
		{

		}
		else if (!sncmp(n, "vt", 2))
		{

		}
		else if (!sncmp(n, "f", 1))
		{

		}
	}
	if (fclose(f) == EOF)
		return (print_error("Failed to close file !\n", 0));*/
	return (1);
}
