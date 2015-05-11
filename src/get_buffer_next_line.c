
#include <stdlib.h>
#include "core.h"

char				*get_buffer_next_line(char *file, int *file_size,
										int *offset, int *line_size)
{
	char			*line;
	int				i;

	if (*offset >= *file_size)
		return (NULL);
	if ((*line_size = get_buffer_next_line_size(file, offset)) == -1)
		return (NULL);
	if (!(line = (char *)malloc(sizeof(char) * *line_size + 1)))
		return (print_error_p("Failed to allocate memory !\n"));
	i = 0;
	while (file[*offset + i] != '\n' && file[*offset + i] != '\0')
	{
		line[i] = file[*offset + i];
		i++;
	}
	line[*line_size] = '\0';
	*offset += *line_size + 1;
	return (line);
}
