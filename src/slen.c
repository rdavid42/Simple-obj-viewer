
#include <unistd.h>

int				slen(char const *s)
{
	int			i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}