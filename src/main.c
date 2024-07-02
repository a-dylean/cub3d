#include "../includes/cub3d.h"

void	init_struct(t_cub *cub, char *filename)
{
	(void)filename;
	cub->map = NULL;
	cub->map_height = 0;
	cub->txtr = NULL;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	// cub->win_height = 0;
	// cub->win_width = 0;
	cub->textures.img_ptr_north = NULL;
	cub->textures.img_ptr_south = NULL;
	cub->textures.img_ptr_east = NULL;
	cub->textures.img_ptr_west = NULL;
	cub->player.x = 0;
	cub->player.y = 0;
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0;
	cub->player.delta_camera_x = 0;
	cub->textures.floor_color = -1;
	cub->textures.ceiling_color = -1;
}

int	load_textures(t_cub *cub) // replace the textures with the correct paths, after parsing
{
	int	pos[2];

	cub->textures.img_ptr_north = mlx_xpm_file_to_image(cub->mlx_ptr,
			"assets/Walls/b&w_bricks.xpm", &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_north)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
			// implement proper freeing of all the previous allocations for images in case of error + exit program
	cub->textures.img_ptr_south = mlx_xpm_file_to_image(cub->mlx_ptr,
			"assets/Walls/b&w_dots.xpm", &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_south)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
	cub->textures.img_ptr_west = mlx_xpm_file_to_image(cub->mlx_ptr,
			"assets/Walls/b&w_squiggles.xpm", &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_south)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
	cub->textures.img_ptr_east = mlx_xpm_file_to_image(cub->mlx_ptr,
			"assets/Walls/b&w_star.xpm", &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_east)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub cub;
	if (argc == 2)
	{
		init_struct(&cub, argv[1]);
		parsing(argv[1], &cub);
		set_player(&cub, &cub.player);
		cub.mlx_ptr = mlx_init();
		if (!cub.mlx_ptr)
			return (1);
		cub.win_ptr = mlx_new_window(cub.mlx_ptr, WIDTH, HEIGHT, "cub3d");
		if (!cub.win_ptr)
			return (free(cub.mlx_ptr), 1);
		load_textures(&cub);
		mlx_loop_hook(cub.mlx_ptr, &cast_ray, &cub);
		mlx_hook(cub.win_ptr, 17, 1L << 17, &destroyer, &cub);
		mlx_hook(cub.win_ptr, KeyPress, KeyPressMask, &key_press, &cub);
		mlx_loop(cub.mlx_ptr);
	}
	else
	{
		printf("WRONG INPUT! Try: ./cub3d [PATH TO MAP]\n");
	}
	return (0);
}
