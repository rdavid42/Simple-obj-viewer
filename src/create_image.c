/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:52:39 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:52:40 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			create_image(t_window *w, t_image *img)
{
	img->data = mlx_new_image(w->mlx_init, w->width, w->height);
	get_image_data(img);
	return (1);
}
