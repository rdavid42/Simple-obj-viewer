
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
}

static int				get_bmp_info(t_bmp *bmp)
{
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
	return (1);
}

void					*load_bmp(char const *filename, t_bmp *bmp_ret)
{
	int					fd;
	t_bmp				bmp;
	unsigned char		*data;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (perror_ret(FILE_E1));
	if (read(fd, bmp.bmp_header, BMP_HEADER_SIZE) == -1)
		return (perror_ret(HEADER_E1));
	if (read(fd, bmp.dib_header, DIB_HEADER_SIZE) == -1)
		return (perror_ret(HEADER_E3));
	if (!get_bmp_info(&bmp))
		return (NULL);
	if (!(data = (unsigned char *)malloc(bmp.raw_bmp_size)))
		return (perror_ret(MALLOC_E1));
	if (read(fd, data, bmp.raw_bmp_size) == -1)
		return (perror_ret(DATA_E1));
	close(fd);
	if (bmp_ret != NULL)
		*bmp_ret = bmp;
	print_bmp_info(&bmp);
	return ((void *)data);
}
