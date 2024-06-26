#include "cub3d.h"

int	destroyer(t_cub *cub)
{
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		destroyer(cub);
	return (0);
}

void	init_struct(t_cub *cub, char *filename)
{
	cub->map = NULL;
	cub->map_height = get_map_height(filename);
	cub->map_width = 0;
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
	cub->textures.floor_color = YELLOW; // change to real colors taken from map parsing
	cub->textures.ceiling_color = WHITE;
}

int	load_textures(t_cub *cub) // replace the textures with the correct paths, after parsing
{
	int pos[2];
	cub->textures.img_ptr_north = mlx_xpm_file_to_image(cub->mlx_ptr,
			"assets/Walls/light_brick.xpm", &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_north)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
			// implement proper freeing of all the previous allocations for images in case of error + exit program
	cub->textures.img_ptr_south = mlx_xpm_file_to_image(cub->mlx_ptr,
			"assets/Walls/diamond.xpm", &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_south)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
	cub->textures.img_ptr_south = mlx_xpm_file_to_image(cub->mlx_ptr,
			"assets/Walls/light_gravel.xpm", &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_south)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
	cub->textures.img_ptr_east = mlx_xpm_file_to_image(cub->mlx_ptr,
			"assets/Walls/emerald.xpm", &pos[0], &pos[1]);
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
		parse_input(argv[1], &cub);
		set_player(&cub, &cub.player);
		cub.mlx_ptr = mlx_init();
		if (!cub.mlx_ptr)
			return (1);
		cub.win_ptr = mlx_new_window(cub.mlx_ptr, WIDTH, HEIGHT, "cub3d"); // replace 800 and 600 with the calculated win height and length
		if (!cub.win_ptr)
			return (free(cub.mlx_ptr), 1);
		// load_textures(&cub);
		// mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr,
		// 	cub.textures.img_ptr_north, 0, 0);
		mlx_loop_hook(cub.mlx_ptr, &cast_ray, &cub);
		mlx_hook(cub.win_ptr, 17, 1L << 17, &destroyer, &cub);
		mlx_hook(cub.win_ptr, KeyRelease, KeyReleaseMask, &key_press, &cub);
		mlx_loop(cub.mlx_ptr);
	}
	else
	{
		printf("WRONG INPUT! Try: ./cub3d [PATH TO MAP]\n");
	}
	free_map(cub.map);
	// free_textures(cub.textures);
	// free images

	return (0);
}