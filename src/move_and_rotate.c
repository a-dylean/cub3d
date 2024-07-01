/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:02:05 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/01 14:10:26 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
