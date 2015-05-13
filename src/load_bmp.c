/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:54:01 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:54:01 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "bmp_loader.h"

static void				*perror_ret(char const *msg)
{
	perror(msg);
	return (NULL);
}

static int				error_msg(char const *msg)
{
	int					size;

	size = 0;
	while (msg[size])
		size++;
	if (write(2, msg, size) == -1)
		return (0);
	return (0);
}

static int				get_bmp_info(int fd, t_bmp *bmp)
{
	int					unused_header_size;
	unsigned char		*unused_header;

	if (*(uint16_t *)&bmp->bmp_header[0] != 0x4D42)
		return (error_msg(HEADER_E2));
	bmp->bmp_size = *(uint32_t *)&bmp->bmp_header[2];
	bmp->data_offset = *(uint32_t *)&bmp->bmp_header[10];
	bmp->width = *(uint32_t *)&bmp->dib_header[4];
	bmp->height = *(uint32_t *)&bmp->dib_header[8];
	if ((bmp->bpp = *(uint16_t *)&bmp->dib_header[14]) != 24)
		return (error_msg(BPP_E1));
	if ((bmp->compression = *(uint32_t *)&bmp->dib_header[16]) != BI_RGB)
		return (error_msg(COMPRESSION_E1));
	bmp->raw_bmp_size = *(uint32_t *)&bmp->dib_header[20];
	unused_header_size = bmp->data_offset - (BMP_HSIZE + DIB_HSIZE);
	if (!bmp->raw_bmp_size)
		bmp->raw_bmp_size = bmp->bmp_size - (BMP_HSIZE + DIB_HSIZE);
	if (unused_header_size > 0)
	{
		unused_header = (unsigned char *)malloc(unused_header_size);
		read(fd, unused_header, unused_header_size);
		free(unused_header);
	}
	return (1);
}

static int				write_data(t_bmp *bmp, unsigned char *data, int fd)
{
	unsigned char		buf[3];
	uint32_t			i;
	uint32_t			j;
	uint32_t			k;

	k = 0;
	i = 0;
	while (i < bmp->height)
	{
		j = 0;
		while (j < bmp->width)
		{
			if (read(fd, buf, 3) == -1)
				return (0);
			data[k++] = buf[2];
			data[k++] = buf[1];
			data[k++] = buf[0];
			j++;
		}
		if (j % 4)
			if (read(fd, buf, 1) == -1)
				return (0);
		i++;
	}
	return (1);
}

void					*load_bmp(char const *filename, t_bmp *bmp_ret)
{
	int					fd;
	t_bmp				bmp;
	unsigned char		*data;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (perror_ret(FILE_E1));
	if (read(fd, bmp.bmp_header, BMP_HSIZE) == -1)
		return (perror_ret(HEADER_E1));
	if (read(fd, bmp.dib_header, DIB_HSIZE) == -1)
		return (perror_ret(HEADER_E3));
	if (!get_bmp_info(fd, &bmp))
		return (NULL);
	if (!(data = (unsigned char *)malloc(sizeof(unsigned char)
										* bmp.raw_bmp_size)))
		return (perror_ret(MALLOC_E1));
	if (!write_data(&bmp, data, fd))
		return (NULL);
	close(fd);
	if (bmp_ret != NULL)
		*bmp_ret = bmp;
	return (data);
}
