
#include "core.h"

void		put_pixel(t_image *img, int const *x, int const *y, int const *cl)
{
	int const		res = ((*x) * (img->bpp / sizeof(char *))
						+ ((*y) * img->sizeline));

	img->p_data[res] = *cl;
	img->p_data[res + 1] = (*cl) >> 8;
	img->p_data[res + 2] = (*cl) >> 16;
}
