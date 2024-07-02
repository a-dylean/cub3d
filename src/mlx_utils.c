/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:01:41 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/01 12:01:50 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	destroyer(t_cub *cub)
{
	free_map(cub->map);
	free_textures(cub->txtr);
	mlx_destroy_image(cub->mlx_ptr, cub->textures.img_ptr_north);
	mlx_destroy_image(cub->mlx_ptr, cub->textures.img_ptr_south);
	mlx_destroy_image(cub->mlx_ptr, cub->textures.img_ptr_east);
	mlx_destroy_image(cub->mlx_ptr, cub->textures.img_ptr_west);
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		destroyer(cub);
	else if (keycode == XK_w)
		move_player(cub, cub->player.dir_y, cub->player.dir_x);
	else if (keycode == XK_s)
		move_player(cub, -cub->player.dir_y, -cub->player.dir_x);
	else if (keycode == XK_a)
		move_player(cub, cub->player.dir_x, -cub->player.dir_y);
	else if (keycode == XK_d)
		move_player(cub, -cub->player.dir_x, cub->player.dir_y);
	else if (keycode == XK_Left)
		rotate_player(cub, 0.09);
	else if (keycode == XK_Right)
		rotate_player(cub, -0.09);
	return (0);
}
