
#include "core.h"

void		get_image_data(t_image *img)
{
	img->p_data = mlx_get_data_addr(img->data, &img->bpp, &img->sizeline, &img->endian);
}
