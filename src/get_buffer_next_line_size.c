/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_buffer_next_line_size.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:53:13 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:53:14 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int					get_buffer_next_line_size(char *file, int *offset)
{
	int				size;

	size = 0;
	while (file[*offset + size] != '\n')
	{
		if (!file[*offset + size])
			return (-1);
		size++;
	}
	return (size);
}
