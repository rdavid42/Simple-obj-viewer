/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:59:12 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:59:13 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		put_pixel(t_image *img, int const *x, int const *y, int const *cl)
{
	int const		res = ((*x) * (img->bpp / sizeof(char *))

	+ ((*y) * img->sizeline));
	img->p_data[res] = *cl;
	img->p_data[res + 1] = (*cl) >> 8;
	img->p_data[res + 2] = (*cl) >> 16;
}
