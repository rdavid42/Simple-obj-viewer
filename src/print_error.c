
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
