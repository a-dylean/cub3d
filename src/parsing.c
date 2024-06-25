#include "cub3d.h"

void parse_input(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_with_error("No such file or directory");
	
}