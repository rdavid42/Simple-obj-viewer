/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:59:37 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:59:37 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"

void				release_object(t_object *o)
{
	if (o->vertices != NULL)
		free(o->vertices);
	if (o->indices != NULL)
		free(o->indices);
}
