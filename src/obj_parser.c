
#include <stdio.h>
#include <stdlib.h>
#include "core.h"

int					parse_obj(char const *filename)
{
	char			n[256];
	FILE			*f;
	int				r;

	if (!(f = fopen(filename, "r")))
		return (0);
	while ((r = fscanf(f, "%s", n)) != EOF)
	{

	}
	return (1);
}