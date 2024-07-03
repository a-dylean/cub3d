/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:06:22 by atonkopi          #+#    #+#             */
/*   Updated: 2024/07/02 15:10:37 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	invalid_commas(char *line, char **color_ids, t_cub *cub)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (line[i])
	{
		if (line[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
	{
		free_array(color_ids);
		free(line);
		clean_up(cub, "Invalid color declaration");
	}
	return ;
}

void	colors_errors_check(t_cub *cub)
{
	if (cub->textures.floor_color < 0 || cub->textures.ceiling_color < 0)
		clean_up(cub, "Missing color(s) definition");
	return ;
}

int	is_color(char *id)
{
	if (!id)
		return (0);
	return (ft_strncmp(id, "F", 2) == 0 || ft_strncmp(id, "C", 2) == 0);
}

int	get_rgb_int(char **colors)
{
	int	int_colors[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!str_is_numeric(colors[i]))
			return (-1);
		int_colors[i] = ft_atoi(colors[i]);
		if (int_colors[i] < 0 || int_colors[i] > 255)
			return (-1);
		i++;
	}
	return ((int_colors[0] << 16) | (int_colors[1] << 8) | int_colors[2]);
}
