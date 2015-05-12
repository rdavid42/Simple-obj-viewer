/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 10:09:06 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 10:09:08 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <stddef.h>
# include <openGL/gl3.h>
# include <openGL/gl3ext.h>
# include <mlx.h>
# include "mlx_opengl.h"

# define TEXTURE_MAX			5

# define BUFSIZE				16384

# define WW						1920
# define WH						1080

# define MOTION_MASK			(1 << 6)
# define MOTION					6
# define K_ESC					53
# define K_LEFT					123
# define K_RIGHT				124
# define K_UP					126
# define K_DOWN					125
# define K_A					0
# define K_T					17
# define K_KPLUS				69
# define K_KMIN					78
# define M_LEFT					1
# define M_RIGHT				2
# define M_S_UP					4
# define M_S_DOWN				5
# define K_MULT					67
# define K_DIV					75
# define K_N1					84
# define K_1					18
# define K_N2					85
# define K_2					19
# define K_N3					86
# define K_3					20
# define K_HOME					115
# define K_END					119

# define TRANSLATE_SPEED		0.1f

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef struct		s_object
{
	int				vertices_size;
	int				indices_size;
	GLfloat			*vertices;
	GLushort		*indices;
	GLuint			vao_id;
	GLuint			vbo_ids[2];
}					t_object;

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
	GLuint			anim_loc;
	GLuint			y_deg_loc;
	GLuint			tex_enabled_loc;
	GLuint			position_loc;
	GLuint			color_loc;
	GLuint			proj_loc;
	GLuint			view_loc;
	GLuint			tex_scale_loc;
	GLuint			rotations_loc;
	t_vec			rotations;
	float			tex_scale;
	float			anim;
	t_vec			translate;
	float			y_deg;
	float			tex_enabled;
	t_vec			cam_pos;
	t_vec			cam_look_at;
	float			proj_matrix[16];
	float			view_matrix[16];
	void			*mlx_init;
	t_object		otest;
	int				texture_max;
	int				current_texture;
	GLuint			textures[TEXTURE_MAX];
	GLuint			vertex_shader;
	GLuint			fragment_shader;
	GLuint			geometry_shader;
	GLuint			program;
	t_window		window;
}					t_core;

int					scmp(const char *s1, const char *s2, size_t n);
void				put_pixel(t_image *img, int const *x, int const *y,
								int const *cl);
int					slen(char const *s);
int					sncmp(char const *s1, char const *s2, size_t n);
GLuint				load_shader(GLenum type, char const *filename);
int					compile_shader(GLuint shader, char const *filename);
int					init_shaders(t_core *c);
char				*read_file(char const *filename);
int					print_error(char const *msg, int const code);
void				*print_error_p(char const *msg);
int					parse_object(char const *filename, t_object *o);
int					loop_hook(t_core *c);
void				cross_product(t_vec *a, t_vec *b, t_vec *r);
void				normalize(t_vec *a);
void				set_identity_matrix(float *mat, int size);
void				multiply_matrix(float *a, float *b);
void				set_translation_matrix(float *mat, float x,
											float y, float z);
void				build_projection_matrix(t_core *c, float fov,
											float near_p, float far_p);
t_vec				create_vec(float x, float y, float z);
void				set_view_matrix(float *view_matrix, t_vec *dir,
									t_vec *right, t_vec *up);
void				set_camera(float *view_matrix, t_vec pos, t_vec look_at);
int					expose_hook(t_core *core);
void				get_image_data(t_image *img);
void				update_image(t_window *window);
void				change_rotation(float *rot);
int					key_hook(unsigned int key, t_core *c);
int					key_hook_repeat(unsigned int key, t_core *c);
int					mouse_hook(int button, int x, int y, t_core *core);
int					mouse_event(int x, int y, t_core *core);
int					create_image(t_window *w, t_image *img);
void				check_gl_error(int code);
int					create_window(t_core *core);
int					loop_hook(t_core *c);
void				get_locations(t_core *c);
void				create_buffers(t_core *c);
GLuint				load_texture(char const *filename);
int					initialize_core(t_core *c);
void				release_object(t_object *o);
void				init_object(t_object *o);
int					alloc_object(t_object *o);
int					get_buffer_next_line_size(char *file, int *offset);
char				*get_buffer_next_line(char *file, int *file_size,
										int *offset, int *line_size);
void				load_textures(t_core *c);

#endif
