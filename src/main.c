#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		parse_input(argv[1]);
	}
	else
		printf("WRONG INPUT! Try: ./cub3d [PATH TO MAP]");
	return (0);
}