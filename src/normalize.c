/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:58:58 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:58:58 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"

void		normalize(t_vec *a)
{
	float const		magnitude = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);

	a->x /= magnitude;
	a->y /= magnitude;
	a->z /= magnitude;
}
