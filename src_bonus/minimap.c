/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:48:07 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/03 09:38:18 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	draw_square(t_cub *cub, int x, int y, int color)
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

static void	draw_player_minimap(t_cub *cub, int tile_size,
	int complementary_color)
{
	if (((~cub->textures.ceiling_color) & 0xFFFFFF) == complementary_color)
		complementary_color = BLUE;
	else
		complementary_color = (~cub->textures.ceiling_color) & 0xFFFFFF;
	draw_square(cub, (int)(cub->player.x * tile_size),
		(int)(cub->player.y * tile_size), complementary_color);
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
				draw_square(cub, j * tile_size, i * tile_size,
					complementary_color);
			else if (cub->map[i][j] != ' ' && cub->map[i][j] != '1'
				&& cub->map[i][j] != '\n')
				draw_square(cub, j * tile_size, i * tile_size,
					WHITE);
			j++;
		}
		i++;
	}
	draw_player_minimap(cub, tile_size, complementary_color);
}
