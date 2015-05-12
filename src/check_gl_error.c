/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gl_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:52:19 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:52:19 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		check_gl_error(int code)
{
	GLenum		err;

	err = glGetError();
	if (err != GL_NO_ERROR)
	{
		if (err == GL_INVALID_ENUM)
			dprintf(2, "(%d) Invalid enum !\n", code);
		else if (err == GL_INVALID_VALUE)
			dprintf(2, "(%d) Invalid value !\n", code);
		else if (err == GL_INVALID_OPERATION)
			dprintf(2, "(%d) Invalid operation !\n", code);
		else if (err == GL_INVALID_FRAMEBUFFER_OPERATION)
			dprintf(2, "(%d) Invalid framebuffer operation !\n", code);
		else if (err == GL_OUT_OF_MEMORY)
			dprintf(2, "(%d) Out of memory !\n", code);
	}
}
