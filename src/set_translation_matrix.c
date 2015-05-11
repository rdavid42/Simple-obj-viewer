
#include "core.h"

void		set_translation_matrix(float *mat, float x, float y, float z)
{
	set_identity_matrix(mat, 4);
	mat[12] = x;
	mat[13] = y;
	mat[14] = z;
}
