/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:56:27 by atonkopi          #+#    #+#             */
/*   Updated: 2024/07/02 15:07:32 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	duplicates_check(char *line, char **colors, char **color_ids,
		t_cub *cub)
{
	if ((cub->textures.ceiling_color >= 0 && line[0] == 'C')
		|| (cub->textures.floor_color >= 0 && line[0] == 'F'))
	{
		free_array(color_ids);
		free_array(colors);
		free(line);
		clean_up(cub, "Duplicate color definitions found");
	}
	return ;
}

void	set_color_value(char *line, char **colors, char **color_ids, t_cub *cub)
{
	int	color;

	duplicates_check(line, colors, color_ids, cub);
	color = get_rgb_int(colors);
	if (color == -1)
	{
		free_array(color_ids);
		free_array(colors);
		free(line);
		clean_up(cub, "Invalid color value");
	}
	if (line[0] == 'F')
		cub->textures.floor_color = color;
	else if (line[0] == 'C')
		cub->textures.ceiling_color = color;
	else
	{
		free_array(color_ids);
		free_array(colors);
		clean_up(cub, "Invalid color identifier");
	}
	free_array(colors);
}

char	**init_colors(char **nodes, char **color_ids, t_cub *cub)
{
	int		i;
	char	**colors;
	char	*temp;

	i = 0;
	colors = ft_calloc(sizeof(char *) * array_len(nodes) + 1, sizeof(char *));
	if (!colors)
	{
		free_array(color_ids);
		clean_up(cub, "Memory allocation failed");
	}
	while (nodes[i])
	{
		temp = ft_strtrim(nodes[i], SPACES);
		colors[i] = ft_strdup(temp);
		if (!colors[i])
		{
			free_array(nodes);
			free_array(color_ids);
			clean_up(cub, "Memory allocation failed");
		}
		free(temp);
		i++;
	}
	return (colors);
}

void	parse_color(char *line, t_cub *cub, char **color_ids)
{
	char	**nodes;
	char	**colors;
	char	*temp;

	invalid_commas(line, color_ids, cub);
	temp = ft_strtrim(line, "FC");
	nodes = ft_split(temp, ',');
	free(temp);
	if (!nodes)
	{
		free(line);
		free_array(color_ids);
		clean_up(cub, "Memory allocation failed");
	}
	if (array_len(nodes) != 3)
	{
		free_array(nodes);
		free_array(color_ids);
		free(line);
		clean_up(cub, "Invalid color declaration");
	}
	colors = init_colors(nodes, color_ids, cub);
	free_array(nodes);
	set_color_value(line, colors, color_ids, cub);
	free(line);
}
