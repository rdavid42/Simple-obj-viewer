/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 10:00:12 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 10:00:13 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		set_camera(float *view_matrix, t_vec pos, t_vec look_at)
{
	t_vec	dir;
	t_vec	right;
	t_vec	up;
	float	aux[16];

	up = create_vec(0.0f, 1.0f, 0.0f);
	dir = create_vec(look_at.x - pos.x, look_at.y - pos.y, look_at.z - pos.z);
	normalize(&dir);
	cross_product(&dir, &up, &right);
	normalize(&right);
	cross_product(&right, &dir, &up);
	normalize(&up);
	set_view_matrix(view_matrix, &dir, &right, &up);
	set_translation_matrix(aux, -pos.x, -pos.y, -pos.z);
	multiply_matrix(view_matrix, aux);
}
