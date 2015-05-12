/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:52:00 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:52:01 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"

int					alloc_object(t_object *o)
{
	if (o->vertices_size > 0)
		if (!(o->vertices =
			(GLfloat *)malloc(sizeof(GLfloat) * o->vertices_size * 6)))
			return (print_error("Failed to allocate vertices !\n", 0));
	if (o->indices_size > 0)
		if (!(o->indices =
			(GLushort *)malloc(sizeof(GLushort) * o->indices_size * 3)))
			return (print_error("Failed to allocate indices !\n", 0));
	return (1);
}
