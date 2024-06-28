#include "../includes/cub3d.h"

void	move_player(t_cub *cub, double dir_x, double dir_y)
{
	if (cub->map[(int)(cub->player.y + dir_y * 0.064)][(int)cub->player.x] != '1')
		cub->player.y += dir_y * 0.064;
	if (cub->map[(int)cub->player.y][(int)(cub->player.x + dir_x * 0.064)] != '1')
		cub->player.x += dir_x * 0.064;
}

void	move_forward(t_cub *cub)
{
	if (cub->map[(int)(cub->player.y + cub->player.dir_x * 0.1)][(int)cub->player.x] != '1')
		cub->player.y += cub->player.dir_x * 0.1;
	if (cub->map[(int)cub->player.y][(int)(cub->player.x + cub->player.dir_y * 0.1)] != '1')
		cub->player.x += cub->player.dir_y * 0.1;
}

void	move_backward(t_cub *cub)
{
	if (cub->map[(int)(cub->player.y - cub->player.dir_x * 0.1)][(int)cub->player.x] != '1')
		cub->player.y -= cub->player.dir_x * 0.1;
	if (cub->map[(int)cub->player.y][(int)(cub->player.x - cub->player.dir_y * 0.1)] != '1')
		cub->player.x -= cub->player.dir_y * 0.1;
}

void	move_left(t_cub *cub)
{
	if (cub->map[(int)(cub->player.y - cub->player.dir_y * 0.1)][(int)cub->player.x] != '1')
		cub->player.y -= cub->player.dir_y * 0.1;
	if (cub->map[(int)cub->player.y][(int)(cub->player.x + cub->player.dir_x * 0.1)] != '1')
		cub->player.x += cub->player.dir_x * 0.1;
}

void	move_right(t_cub *cub)
{
	if (cub->map[(int)(cub->player.y + cub->player.dir_y * 0.1)][(int)cub->player.x] != '1')
		cub->player.y += cub->player.dir_y * 0.1;
	if (cub->map[(int)cub->player.y][(int)(cub->player.x - cub->player.dir_x * 0.1)] != '1')
		cub->player.x -= cub->player.dir_x * 0.1;
}
