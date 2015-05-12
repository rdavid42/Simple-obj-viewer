/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_projection_matrix.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:52:05 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:52:05 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		build_projection_matrix(t_core *c, float fov,
									float near_p, float far_p)
{
	float const		f = 1.0f / tan(fov * (M_PI / 360.0));
	float const		ratio = (1.0f * c->window.width) / c->window.height;

	set_identity_matrix(c->proj_matrix, 4);
	c->proj_matrix[0] = f / ratio;
	c->proj_matrix[1 * 4 + 1] = f;
	c->proj_matrix[2 * 4 + 2] = (far_p + near_p) / (near_p - far_p);
	c->proj_matrix[3 * 4 + 2] = (2.0f * far_p * near_p) / (near_p - far_p);
	c->proj_matrix[2 * 4 + 3] = -1.0f;
	c->proj_matrix[3 * 4 + 3] = 0.0f;
}
