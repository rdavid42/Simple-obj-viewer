
#include "core.h"

void		set_view_matrix(float *view_matrix, t_vec *dir,
							t_vec *right, t_vec *up)
{
	view_matrix[0] = right->x;
	view_matrix[4] = right->y;
	view_matrix[8] = right->z;
	view_matrix[12] = 0.0f;
	view_matrix[1] = up->x;
	view_matrix[5] = up->y;
	view_matrix[9] = up->z;
	view_matrix[13] = 0.0f;
	view_matrix[2] = -dir->x;
	view_matrix[6] = -dir->y;
	view_matrix[10] = -dir->z;
	view_matrix[14] = 0.0f;
	view_matrix[3] = 0.0f;
	view_matrix[7] = 0.0f;
	view_matrix[11] = 0.0f;
	view_matrix[15] = 1.0f;
}
