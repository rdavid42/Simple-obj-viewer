
#include "core.h"

void		set_identity_matrix(float *mat, int size)
{
	int				i;
	int const		s2 = size * size;

	i = 0;
	while (i < s2)
	{
		mat[i] = 0.0f;
		i++;
	}
	i = 0;
	while (i < size)
	{
		mat[i + i * size] = 1.0f;
		i++;
	}
}
