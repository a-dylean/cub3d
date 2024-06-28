/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:27:28 by jlabonde          #+#    #+#             */
/*   Updated: 2024/06/28 08:54:24 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
