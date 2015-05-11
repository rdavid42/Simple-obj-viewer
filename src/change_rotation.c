
#include "core.h"

void		change_rotation(float *rot)
{
	*rot += 1.0f;
	if (*rot == 2.0f)
		*rot = -1.0f;
}
