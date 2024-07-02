/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:02:05 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/01 14:06:56 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	move_player(t_cub *cub, double dir_x, double dir_y)
{
	double	speed;
	int		new_y;
	int		new_x;

	speed = 0.064;
	new_y = (int)(cub->player.y + dir_y * (speed));
	new_x = (int)(cub->player.x + dir_x * (speed));
	if (cub->map[new_y][(int)cub->player.x] != '1')
		cub->player.y += dir_y * (speed);
	if (cub->map[(int)cub->player.y][new_x] != '1')
		cub->player.x += dir_x * (speed);
}

void	rotate_player(t_cub *cub, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir_x;
	old_plane_x = cub->player.plane_x;
	cub->player.dir_x = cub->player.dir_x * cos(rotation_speed)
		- cub->player.dir_y * sin(rotation_speed);
	cub->player.dir_y = old_dir_x * sin(rotation_speed)
		+ cub->player.dir_y * cos(rotation_speed);
	cub->player.plane_x = cub->player.plane_x * cos(rotation_speed)
		- cub->player.plane_y * sin(rotation_speed);
	cub->player.plane_y = old_plane_x * sin(rotation_speed)
		+ cub->player.plane_y * cos(rotation_speed);
}

int	mouse_move(int x, int y, t_cub *cub)
{
	int	delta_x;

	(void)y;
	delta_x = x - WIDTH / 2;
	if (delta_x > 0 || delta_x > cub->player.delta_camera_x)
		rotate_player(cub, -0.01);
	else if (delta_x < 0 || delta_x < cub->player.delta_camera_x)
		rotate_player(cub, 0.01);
	cub->player.delta_camera_x = delta_x;
	return (0);
}
