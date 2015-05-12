/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:53:51 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:53:51 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"

int			key_hook(unsigned int key, t_core *c)
{
	if (key == K_ESC)
	{
		release_object(&c->otest);
		exit(0);
	}
	else if (key == K_A)
		c->anim = !c->anim;
	else if (key == K_T)
		c->tex_enabled = !c->tex_enabled;
	else if (key == K_1 || key == K_N1)
		change_rotation(&c->rotations.x);
	else if (key == K_2 || key == K_N2)
		change_rotation(&c->rotations.y);
	else if (key == K_3 || key == K_N3)
		change_rotation(&c->rotations.z);
	return (1);
}
