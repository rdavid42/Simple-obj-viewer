
#include "core.h"

void		cross_product(t_vec *a, t_vec *b, t_vec *r)
{
	r->x = a->y * b->z - b->y * a->z;
	r->y = a->z * b->x - b->z * a->x;
	r->z = a->x * b->y - b->x * a->y;
}
