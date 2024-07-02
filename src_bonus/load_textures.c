/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:36:51 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/02 14:37:33 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	handle_texture_init_error(t_cub *cub, int to_free)
{
	if (to_free >= 1)
		mlx_destroy_image(cub->mlx_ptr, cub->textures.img_ptr_north);
	if (to_free >= 2)
		mlx_destroy_image(cub->mlx_ptr, cub->textures.img_ptr_south);
	if (to_free >= 3)
		mlx_destroy_image(cub->mlx_ptr, cub->textures.img_ptr_west);
	free(cub->mlx_ptr);
	free(cub->win_ptr);
	return (1);
}

static char	*texture_path(t_cub *cub, int orientation)
{
	t_txtr	*current;

	current = cub->txtr;
	while (current)
	{
		if (ft_strncmp(current->orientation, "NO", 2) == 0
			&& orientation == NORTH)
			return (current->path);
		if (ft_strncmp(current->orientation, "SO", 2) == 0
			&& orientation == SOUTH)
			return (current->path);
		if (ft_strncmp(current->orientation, "WE", 2) == 0
			&& orientation == WEST)
			return (current->path);
		if (ft_strncmp(current->orientation, "EA", 2) == 0
			&& orientation == EAST)
			return (current->path);
		current = current->next;
	}
	return (NULL);
}

int	load_textures(t_cub *cub)
{
	int	pos[2];

	cub->textures.img_ptr_north = mlx_xpm_file_to_image(cub->mlx_ptr,
			texture_path(cub, NORTH), &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_north)
		return (free(cub->mlx_ptr), free(cub->win_ptr), 1);
	cub->textures.img_ptr_south = mlx_xpm_file_to_image(cub->mlx_ptr,
			texture_path(cub, SOUTH), &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_south)
		return (handle_texture_init_error(cub, 1));
	cub->textures.img_ptr_west = mlx_xpm_file_to_image(cub->mlx_ptr,
			texture_path(cub, WEST), &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_west)
		return (handle_texture_init_error(cub, 2));
	cub->textures.img_ptr_east = mlx_xpm_file_to_image(cub->mlx_ptr,
			texture_path(cub, EAST), &pos[0], &pos[1]);
	if (!cub->textures.img_ptr_east)
		return (handle_texture_init_error(cub, 3));
	return (0);
}
