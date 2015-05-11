
#include "core.h"

void				init_object(t_object *o)
{
	o->vertices_size = 0;
	o->indices_size = 0;
	o->vertices = NULL;
	o->indices = NULL;
}
