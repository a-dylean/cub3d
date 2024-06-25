#include "cub3d.h"


void init_cube(char *filename, t_cub *cub)
{
	cub->map = NULL;
	cub->map_height = get_map_height(filename);
	cub->map_width = 0;
	cub->textures = NULL;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc == 2)
	{
		init_cube(argv[1], &cub);
		parse_input(argv[1], &cub);
	}
	else
		printf("WRONG INPUT! Try: ./cub3d [PATH TO MAP]\n");
	free_map(cub.map);
	// free_txtr(cub.textures);
	return (0);
}