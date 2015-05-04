#ifndef CORE_H
# define CORE_H

# include <stddef.h>
# include <mlx.h>
# include "mlx_opengl.h"

# define WW						1920
# define WH						1080

# define MOTION_MASK			(1 << 6)
# define MOTION					6
# define K_ESC					53
# define K_LEFT					123
# define K_RIGHT				124
# define K_UP					126
# define K_DOWN					125
# define K_KPLUS				69
# define K_KMIN					78
# define M_LEFT					1
# define M_RIGHT				2
# define M_S_UP					4
# define M_S_DOWN				5

typedef struct		s_image
{
	char			*p_data;
	void			*data;
	unsigned int	*device_array;
	unsigned int	*host_array;
	int				bpp;
	int				sizeline;
	int				endian;
}					t_image;

typedef struct		s_window
{
	void			*mlx_init;
	void			*init;
	int				width;
	int				height;
	t_image			img;
	int				mx;
	int				my;
}					t_window;

typedef struct		s_core
{
	void			*mlx_init;
	t_window		window;
}					t_core;

int					scmp(const char *s1, const char *s2, size_t n);
void				put_pixel(t_image *img, int const *x, int const *y,
								int const *cl);
int					slen(char const *s);

#endif