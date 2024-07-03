/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:26:46 by atonkopi          #+#    #+#             */
/*   Updated: 2024/07/03 09:49:33 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	clean_up(t_cub *cub, char *error)
{
	if (cub->config_info)
		free_array(cub->config_info);
	if (cub->map)
		free_map(cub->map);
	if (cub->txtr)
		free_textures(cub->txtr);
	if (error)
		exit_with_error(error);
}

void	free_and_exit(char *msg, t_cub *cub, char *new_line)
{
	if (ft_strlen(new_line) > 0)
		free(new_line);
	free_map(cub->map);
	exit_with_error(msg);
}

void	exit_with_error(char *error)
{
	printf("Error\n");
	printf("%s\n", error);
	exit(1);
}
