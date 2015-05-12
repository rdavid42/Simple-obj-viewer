/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_locations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:53:23 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:53:23 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		get_locations(t_core *c)
{
	c->position_loc = glGetAttribLocation(c->program, "position");
	c->color_loc = glGetAttribLocation(c->program, "in_color");
	c->y_deg_loc = glGetUniformLocation(c->program, "y_deg");
	c->tex_scale_loc = glGetUniformLocation(c->program, "tex_scale");
	c->tex_enabled_loc = glGetUniformLocation(c->program, "vert_tex_enabled");
	c->rotations_loc = glGetUniformLocation(c->program, "rot");
	c->anim_loc = glGetUniformLocation(c->program, "anim");
	c->proj_loc = glGetUniformLocation(c->program, "proj_matrix");
	c->view_loc = glGetUniformLocation(c->program, "view_matrix");
}
