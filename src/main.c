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

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_cub cub;
	cub.mlx_ptr = mlx_init();
	if (!cub.mlx_ptr)
		return (1);
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, 800, 600, "cub3d"); // replace 800 and 600 with the calculated win height and length
	if (!cub.win_ptr)
		return (free(cub.mlx_ptr), 1);
	mlx_hook(cub.win_ptr, 17, 1L << 17, &destroyer, &cub);
	mlx_hook(cub.win_ptr, KeyRelease, KeyReleaseMask, &key_press, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}