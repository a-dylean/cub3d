#include "cub3d.h"

int	destroyer(t_cub *cub)
{
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	exit(0);
	return (0);
}

/*added the direction variable for more readbility in the key_press function,
can be deleted */
void	move_player(int direction, t_cub *cub, int x, int y)
{
	(void)direction;
	int new_y;
	int new_x;

	new_y = (int)(cub->player.y + y);
	new_x = (int)(cub->player.x + x);
	if (cub->map[new_y][new_x] == '0')
	{
		cub->player.x += x;
		cub->player.y += y;
	}
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		destroyer(cub);
	else if (keycode == XK_w)
		move_player(UP, cub, 0, -1);
	else if (keycode == XK_s)
		move_player(DOWN, cub, 0, 1);
	else if (keycode == XK_a)
		move_player(LEFT, cub, -1, 0);
	else if (keycode == XK_d)
		move_player(RIGHT, cub, 1, 0);
	return (0);
}
