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
	else if (keycode == XK_w)
		move_forward(cub);
	else if (keycode == XK_s)
		move_backward(cub);
	else if (keycode == XK_a)
		move_left(cub);
	else if (keycode == XK_d)
		move_right(cub);
	else if (keycode == XK_Left || keycode == XK_Right)
		rotate_player(keycode, cub, 0.05);

	return (0);
}
