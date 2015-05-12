/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sncmp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:59:58 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:59:59 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		sncmp(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if (s1 != NULL || s2 != NULL)
	{
		i = 0;
		while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
		{
			if ((unsigned char)s1[i] != (unsigned char)s2[i])
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			i++;
		}
	}
	return (0);
}
