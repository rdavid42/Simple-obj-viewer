
#include <stdlib.h>
#include "core.h"

void				release_object(t_object *o)
{
	if (o->vertices != NULL)
		free(o->vertices);
	if (o->indices != NULL)
		free(o->indices);
}
