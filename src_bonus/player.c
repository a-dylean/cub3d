/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:05:33 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/01 14:07:03 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	set_direction_and_camera(t_cub *cub, t_player *player, int i, int j)
{
	if (cub->map[i][j] == 'N')
	{
		player->dir_x = -1;
		player->plane_y = FIELD_OF_VIEW;
	}
	else if (cub->map[i][j] == 'S')
	{
		player->dir_x = 1;
		player->plane_y = -FIELD_OF_VIEW;
	}
	else if (cub->map[i][j] == 'W')
	{
		player->dir_y = -1;
		player->plane_x = -FIELD_OF_VIEW;
	}
	else if (cub->map[i][j] == 'E')
	{
		player->dir_y = 1;
		player->plane_x = FIELD_OF_VIEW;
	}
}

/*Sets the original position and orientation
and camera view of the player after the map is parsed
Will center the player in the initial block */
void	set_player(t_cub *cub, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
			{
				player->x = (double)j + 0.5;
				player->y = (double)i + 0.5;
				set_direction_and_camera(cub, player, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
