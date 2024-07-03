/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:56:37 by atonkopi          #+#    #+#             */
/*   Updated: 2024/07/03 13:25:49 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_empty_map(t_cub *cub)
{
	int	i;

	i = 0;
	cub->map = malloc(sizeof(char *) * (cub->map_height + 1));
	if (!cub->map)
	{
		free(cub->map);
		exit_with_error("Memory allocation failed");
	}
	while (i <= cub->map_height)
	{
		cub->map[i] = NULL;
		i++;
	}
}

void	populate_map(t_cub *cub)
{
	int		i;
	char	**arr;
	int		flag;

	i = 0;
	arr = cub->config_info;
	flag = 0;
	while (1)
	{
		if (!*arr || i >= cub->map_height)
			break ;
		if (!flag && (*arr == NULL || **arr == '\0' || map_line(*arr) == 0))
		{
			arr++;
			continue ;
		}
		flag = 1;
		if (*arr == NULL || **arr == '\0' || map_line(*arr) == 0)
			clean_up(cub, "Invalid map declaration");
		cub->map[i] = ft_strdup(*arr);
		if (!cub->map[i])
			clean_up(cub, "Memory allocation failed");
		i++;
		arr++;
	}
}

void	parse_textures_and_colors(char **nodes, char *line, t_cub *cub)
{
	if (!nodes)
	{
		free(line);
		free_array(nodes);
		clean_up(cub, "Memory allocation failed");
	}
	if (line && !is_texture(nodes[0]) && !is_color(nodes[0]))
	{
		free(line);
		free_array(nodes);
		clean_up(cub, "Invalid element found in config");
	}
	if (line && is_texture(nodes[0]))
	{
		free(line);
		parse_texture(nodes, cub);
	}
	if (line && is_color(nodes[0]))
	{
		parse_color(line, cub, nodes);
	}
}

void	parse_config(t_cub *cub)
{
	char	**nodes;
	char	*trimmed_line;
	char	**content;

	content = cub->config_info;
	while (1)
	{
		if (!*content)
			break ;
		if (map_line(*content) && !empty_or_spaces_only(*content))
			break ;
		trimmed_line = ft_strtrim(*content, SPACES);
		if (!trimmed_line || ft_strlen(trimmed_line) == 0)
		{
			free(trimmed_line);
			content++;
			continue ;
		}
		nodes = ft_split(trimmed_line, ' ');
		parse_textures_and_colors(nodes, trimmed_line, cub);
		free_array(nodes);
		content++;
	}
}

void	parsing(char *path, t_cub *cub)
{
	if (!valid_format(path))
		exit_with_error("Invalid file format");
	if (read_file_into_memory(path, cub))
		exit_with_error("Error while reading a file");
	parse_config(cub);
	cub->map_height = get_map_height(cub->config_info);
	init_empty_map(cub);
	populate_map(cub);
	validate_map(cub->map, cub->map_height, cub);
	check_map_is_last(cub->config_info, cub);
	textures_errors_check(cub);
	colors_errors_check(cub);
	free_array(cub->config_info);
}
