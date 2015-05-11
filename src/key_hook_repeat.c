
#include "core.h"

int			key_hook_repeat(unsigned int key, t_core *c)
{
	if (key == K_DOWN)
		c->translate.y += TRANSLATE_SPEED;
	else if (key == K_UP)
		c->translate.y -= TRANSLATE_SPEED;
	else if (key == K_LEFT)
		c->translate.z -= TRANSLATE_SPEED;
	else if (key == K_RIGHT)
		c->translate.z += TRANSLATE_SPEED;
	else if (key == K_KPLUS)
		c->translate.x -= TRANSLATE_SPEED;
	else if (key == K_KMIN)
		c->translate.x += TRANSLATE_SPEED;
	else if (key == K_MULT)
		c->tex_scale += 0.1;
	else if (key == K_DIV)
		c->tex_scale -= 0.1;
	return (1);
}
