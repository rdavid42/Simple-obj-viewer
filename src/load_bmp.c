
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

static void				print_bmp_info(t_bmp *bmp)
{
	dprintf(1, "total size: %d bytes\n", bmp->bmp_size);
	dprintf(1, "data offset: %d bytes\n", bmp->data_offset);
	dprintf(1, "width: %d pixels\n", bmp->width);
	dprintf(1, "height: %d pixels\n", bmp->height);
	dprintf(1, "bpp: %d bits\n", bmp->bpp);
	dprintf(1, "data size: %d bytes\n", bmp->raw_bmp_size);
	dprintf(1, "unused header size: %d bytes\n", bmp->data_offset - (BMP_HEADER_SIZE + DIB_HEADER_SIZE));
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
	unused_header_size = bmp->data_offset - (BMP_HEADER_SIZE + DIB_HEADER_SIZE);
	if (unused_header_size > 0)
	{
		unused_header = (unsigned char *)malloc(unused_header_size);
		read(fd, unused_header, unused_header_size);
		free(unused_header);
	}
	return (1);
}

void					*load_bmp(char const *filename, t_bmp *bmp_ret)
{
	int					fd;
	t_bmp				bmp;
	unsigned char		*data;
	unsigned char		buf[3];
	uint32_t			i;
	uint32_t			j;
	uint32_t			k;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (perror_ret(FILE_E1));
	if (read(fd, bmp.bmp_header, BMP_HEADER_SIZE) == -1)
		return (perror_ret(HEADER_E1));
	if (read(fd, bmp.dib_header, DIB_HEADER_SIZE) == -1)
		return (perror_ret(HEADER_E3));
	if (!get_bmp_info(fd, &bmp))
		return (NULL);
	print_bmp_info(&bmp);
	if (!(data = (unsigned char *)malloc(sizeof(unsigned char) * bmp.raw_bmp_size)))
		return (perror_ret(MALLOC_E1));
	k = 0;
	i = 0;
	while (i < bmp.height)
	{
		j = 0;
		while (j < bmp.width)
		{
			read(fd, buf, 3);
			data[k++] = buf[2];
			data[k++] = buf[1];
			data[k++] = buf[0];
			j++;
		}
		if (j % 4)
			read(fd, buf, 1);
		i++;
	}
	/*if (read(fd, data, bmp.raw_bmp_size) == -1)
		return (perror_ret(DATA_E1));*/
	close(fd);
	if (bmp_ret != NULL)
		*bmp_ret = bmp;
	return (data);
}
