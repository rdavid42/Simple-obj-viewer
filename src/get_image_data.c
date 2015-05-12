/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:53:18 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:53:18 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		get_image_data(t_image *img)
{
	img->p_data = mlx_get_data_addr(img->data, &img->bpp,
									&img->sizeline, &img->endian);
}
