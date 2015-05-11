
#include "core.h"

void		normalize(t_vec *a)
{
	float const		magnitude = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);

	a->x /= magnitude;
	a->y /= magnitude;
	a->z /= magnitude;
}
