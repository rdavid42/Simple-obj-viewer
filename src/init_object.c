/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:53:30 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:53:30 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void				init_object(t_object *o)
{
	o->vertices_size = 0;
	o->indices_size = 0;
	o->vertices = NULL;
	o->indices = NULL;
}
