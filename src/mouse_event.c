
#include "core.h"

int			mouse_event(int x, int y, t_core *core)
{
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > core->window.width)
		x = core->window.width;
	if (y > core->window.height)
		y = core->window.height;
	core->window.mx = x;
	core->window.my = y;
	return (1);
}
