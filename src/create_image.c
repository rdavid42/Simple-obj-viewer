
#include "core.h"

int			create_image(t_window *w, t_image *img)
{
	img->data = mlx_new_image(w->mlx_init, w->width, w->height);
	get_image_data(img);
	return (1);
}
