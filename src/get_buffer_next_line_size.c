
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
