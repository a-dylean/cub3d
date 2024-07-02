/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:56:33 by atonkopi          #+#    #+#             */
/*   Updated: 2024/07/02 14:56:34 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture(char *id)
{
	if (!id)
		return (0);
	return (ft_strncmp(id, "NO", 3) == 0 || ft_strncmp(id, "SO", 3) == 0
		|| ft_strncmp(id, "WE", 3) == 0 || ft_strncmp(id, "EA", 3) == 0);
}

char	*get_path(char *line)
{
	int	fd;

	fd = open(line, O_RDONLY);
	if (fd >= 0)
		return (line);
	return (NULL);
}

void	parse_texture(char **nodes, t_cub *cub)
{
	char	*id;
	char	*path;

	if (array_len(nodes) != 2)
	{
		free_array(nodes);
		clean_up(cub, "Invalid texture declaration");
	}
	id = nodes[0];
	path = get_path(nodes[1]);
	if (!path)
	{
		free_array(nodes);
		clean_up(cub, "Invalid texture path");
	}
	add_txtr_back(&cub->txtr, new_txtr(id, path));
}

void	textures_errors_check(t_cub *cub)
{
	if (!cub->txtr)
		clean_up(cub, "No textures found");
	if (list_len(cub->txtr) != 4)
		clean_up(cub, "Invalid number of textures");
	if (has_duplicates(cub->txtr))
		clean_up(cub, "Duplicate texture definitions found");
}
