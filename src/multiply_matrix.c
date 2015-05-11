
#include <string.h>
#include "core.h"

void		multiply_matrix(float *a, float *b)
{
	float	res[16];
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res[j * 4 + i] = 0.0f;
			k = 0;
			while (k < 4)
			{
				res[j * 4 + i] += a[k * 4 + i] * b[j * 4 + k];
				++k;
			}
			++j;
		}
		++i;
	}
	memcpy(a, res, 16 * sizeof(float));
}
