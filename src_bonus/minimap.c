/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:48:07 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/02 09:58:17 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_square(t_cub *cub, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_pixel(cub->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cub *cub)
{
	int	tile_size;
	int	i;
	int	j;

	tile_size = 5;
	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
				draw_square(cub, j * tile_size, i * tile_size, tile_size, WHITE);
			else if (cub->map[i][j] != ' ' && cub->map[i][j] != '1' && cub->map[i][j] != '\n')
				draw_square(cub, j * tile_size, i * tile_size, tile_size, cub->textures.ceiling_color);
			j++;
		}
		i++;
	}
	draw_square(cub, (int)(cub->player.x * tile_size), (int)(cub->player.y * tile_size), tile_size, RED);
}
