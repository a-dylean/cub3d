/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:16:56 by atonkopi          #+#    #+#             */
/*   Updated: 2024/07/03 09:42:04 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	get_map_height(char **config)
{
	int	i;
	int	height;

	i = 0;
	height = 0;
	while (config[i])
	{
		if (map_line(config[i]) && !empty_or_spaces_only(config[i]))
			height++;
		i++;
	}
	return (height);
}

int	count_lines_in_file(char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror(path), EXIT_FAILURE);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
		line = NULL;
	}
	close(fd);
	return (count);
}

int	read_file_into_memory(char *path, t_cub *cub)
{
	int	fd;
	int	i;
	int	line_len;
	int	rows_count;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror(path), EXIT_FAILURE);
	rows_count = count_lines_in_file(path);
	cub->config_info = (char **)malloc(sizeof(char *) * (rows_count + 1));
	if (!cub->config_info)
		return (EXIT_FAILURE);
	i = 0;
	while (1)
	{
		cub->config_info[i] = get_next_line(fd);
		if (!cub->config_info[i])
			break ;
		line_len = ft_strlen(cub->config_info[i]);
		if (line_len > 0 && cub->config_info[i][line_len - 1] == '\n')
			cub->config_info[i][line_len - 1] = '\0';
		i++;
	}
	cub->config_info[i] = NULL;
	return (close(fd), EXIT_SUCCESS);
}
