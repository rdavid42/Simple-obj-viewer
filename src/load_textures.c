
#include "core.h"

void		load_textures(t_core *c)
{
	c->texture_max = TEXTURE_MAX;
	c->current_texture = 0;
	c->textures[0] = load_texture("resources/duck.bmp");
	c->textures[1] = load_texture("resources/kitten.bmp");
	c->textures[2] = load_texture("resources/lava.bmp");
	c->textures[3] = load_texture("resources/water.bmp");
	c->textures[4] = load_texture("resources/tex1.bmp");
}
