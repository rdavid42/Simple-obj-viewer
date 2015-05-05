
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "core.h"

static int			file_size(char const *filename)
{
	int				fd;
	int				ret;
	int				count;
	char			buf[4096];

	if ((fd = open(filename, O_RDONLY, 0644)) == -1)
		return (print_error("Could not open file !\n", -1));
	count = 0;
	while ((ret = read(fd, buf, 4096)) != 0)
	{
		if (ret == -1)
		{
			close(fd);
			return (print_error("Could not read file !\n", -1));
		}
		count += ret;
	}
	close(fd);
	return (count);
}

char				*read_file(char const *filename)
{
	int				size;
	int				fd;
	int				i[2];
	char			buf;
	char			*file;

	if ((size = file_size(filename)) == -1)
		return (print_error_p("Could not get file size !\n"));
	if (!(file = (char *)malloc(sizeof(char) * size + 1)))
		return (print_error_p("Could not allocate memory !\n"));
	if ((fd = open(filename, O_RDONLY, 0644)) == -1)
		return (print_error_p("Could not open file !\n"));
	i[1] = 0;
	while ((i[0] = read(fd, &buf, 1)) != 0)
	{
		if (i[0] == -1)
		{
			close(fd);
			return (print_error_p("Could not read file !\n"));
		}
		file[i[1]] = buf;
		i[1]++;
	}
	file[i[1]] = '\0';
	return (file);
}
