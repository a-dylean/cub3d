/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:48:07 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/02 13:44:46 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;
	int	tile_size;

	tile_size = 5;
	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
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
	int	complementary_color;

	tile_size = 5;
	i = 0;
	complementary_color = (~cub->textures.ceiling_color) & 0xFFFFFF;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
				draw_square(cub, j * tile_size, i * tile_size, complementary_color);
			else if (cub->map[i][j] != ' ' && cub->map[i][j] != '1'
				&& cub->map[i][j] != '\n')
				draw_square(cub, j * tile_size, i * tile_size,
					cub->textures.ceiling_color);
			j++;
		}
		i++;
	}
	if (((~cub->textures.ceiling_color) & 0x00FFFF) == complementary_color)
		complementary_color = (~cub->textures.ceiling_color) & 0x000FFF;
	else
		complementary_color = (~cub->textures.ceiling_color) & 0x0000FF;
	draw_square(cub, (int)(cub->player.x * tile_size),
		(int)(cub->player.y * tile_size), complementary_color);
}
