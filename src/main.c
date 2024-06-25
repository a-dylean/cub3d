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

void	init_struct(t_cub *cub)
{
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->win_height = 0;
	cub->win_width = 0;
	cub->textures.img_ptr_north = NULL;
	cub->textures.img_ptr_south = NULL;
	cub->textures.img_ptr_east = NULL;
	cub->textures.img_ptr_west = NULL;
}

int	load_textures(t_cub *cub)
{
	cub->textures.img_ptr_north = mlx_xpm_file_to_image(cub->mlx_ptr, "assets/Walls/light_brick.xpm", &cub->win_width, &cub->win_height);
	if (!cub->textures.img_ptr_north)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
	cub->textures.img_ptr_south = mlx_xpm_file_to_image(cub->mlx_ptr, "assets/Walls/diamond.xpm", &cub->win_width, &cub->win_height);
	if (!cub->textures.img_ptr_south)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
	cub->textures.img_ptr_south = mlx_xpm_file_to_image(cub->mlx_ptr, "assets/Walls/light_gravel.xpm", &cub->win_width, &cub->win_height);
	if (!cub->textures.img_ptr_south)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
	cub->textures.img_ptr_east = mlx_xpm_file_to_image(cub->mlx_ptr, "assets/Walls/emerald.xpm", &cub->win_width, &cub->win_height);
	if (!cub->textures.img_ptr_east)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
	return(0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_cub cub;
	init_struct(&cub);
	cub.mlx_ptr = mlx_init();
	if (!cub.mlx_ptr)
		return (1);
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, 800, 600, "cub3d"); // replace 800 and 600 with the calculated win height and length
	if (!cub.win_ptr)
		return (free(cub.mlx_ptr), 1);
	load_textures(&cub);
	mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr, cub.textures.img_ptr_north, 0, 0);
	mlx_hook(cub.win_ptr, 17, 1L << 17, &destroyer, &cub);
	mlx_hook(cub.win_ptr, KeyRelease, KeyReleaseMask, &key_press, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}