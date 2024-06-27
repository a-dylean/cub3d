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
	int		new_x;
	int		new_y;

	new_x = (int)cub->player.x + x;
	new_y = (int)cub->player.y + y;
	if (cub->map[new_y][new_x] == '0')
	{
		cub->player.x += x;
		cub->player.y += y;
	}
}

void	rotate_player(int keycode, t_cub *cub)
{
	double	rotation_speed;
	double	old_dir_x;
	double	old_plane_x;

	rotation_speed = 0.05;
	old_dir_x = cub->player.dir_x;
	old_plane_x = cub->player.plane_x;
	if (keycode == XK_Left)
	{
		cub->player.dir_x = cub->player.dir_x * cos(rotation_speed) - cub->player.dir_y * sin(rotation_speed);
		cub->player.dir_y = old_dir_x * sin(rotation_speed) + cub->player.dir_y * cos(rotation_speed);
		cub->player.plane_x = cub->player.plane_x * cos(rotation_speed) - cub->player.plane_y * sin(rotation_speed);
		cub->player.plane_y = old_plane_x * sin(rotation_speed) + cub->player.plane_y * cos(rotation_speed);
	}
	else if (keycode == XK_Right)
	{
		cub->player.dir_x = cub->player.dir_x * cos(-rotation_speed) - cub->player.dir_y * sin(-rotation_speed);
		cub->player.dir_y = old_dir_x * sin(-rotation_speed) + cub->player.dir_y * cos(-rotation_speed);
		cub->player.plane_x = cub->player.plane_x * cos(-rotation_speed) - cub->player.plane_y * sin(-rotation_speed);
		cub->player.plane_y = old_plane_x * sin(-rotation_speed) + cub->player.plane_y * cos(-rotation_speed);
	}
}
void   mouse_move(int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	(void)cub;
	// printf("Mouse moving in Win3, at %dx%d.\n",x,y);
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
	else if (keycode == XK_Left || keycode == XK_Right)
		rotate_player(keycode, cub);

	return (0);
}
