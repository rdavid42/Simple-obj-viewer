/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:59:07 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:59:07 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "core.h"

int			print_error(char const *msg, int const code)
{
	return (code + 0 * write(2, msg, slen(msg)));
}

void		*print_error_p(char const *msg)
{
	int		ret;

	ret = write(2, msg, slen(msg));
	(void)ret;
	return (NULL);
}
