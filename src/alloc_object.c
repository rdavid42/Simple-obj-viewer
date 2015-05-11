
#include <stdlib.h>
#include "core.h"

int					alloc_object(t_object *o)
{
	if (o->vertices_size > 0)
		if (!(o->vertices =
			(GLfloat *)malloc(sizeof(GLfloat) * o->vertices_size * 6)))
			return (print_error("Failed to allocate vertices !\n", 0));
	if (o->indices_size > 0)
		if (!(o->indices =
			(GLushort *)malloc(sizeof(GLushort) * o->indices_size * 3)))
			return (print_error("Failed to allocate indices !\n", 0));
	return (1);
}
