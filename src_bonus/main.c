/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:39:02 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/03 11:40:40 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_struct(t_cub *cub)
{
	cub->map = NULL;
	cub->map_height = 0;
	cub->txtr = NULL;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->textures.img_ptr_north = NULL;
	cub->textures.img_ptr_south = NULL;
	cub->textures.img_ptr_east = NULL;
	cub->textures.img_ptr_west = NULL;
	cub->player.x = 0;
	cub->player.y = 0;
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0;
	cub->player.delta_camera_x = 0;
	cub->textures.floor_color = -1;
	cub->textures.ceiling_color = -1;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc == 2)
	{
		init_struct(&cub);
		parsing(argv[1], &cub);
		set_player(&cub, &cub.player);
		cub.mlx_ptr = mlx_init();
		if (!cub.mlx_ptr)
			return (1);
		cub.win_ptr = mlx_new_window(cub.mlx_ptr, WIDTH, HEIGHT, "cub3d");
		if (!cub.win_ptr)
			return (free(cub.mlx_ptr), 1);
		load_textures(&cub);
		mlx_loop_hook(cub.mlx_ptr, &cast_ray, &cub);
		mlx_hook(cub.win_ptr, 17, 1L << 17, &destroyer, &cub);
		mlx_hook(cub.win_ptr, KeyPress, KeyPressMask, &key_press, &cub);
		mlx_hook(cub.win_ptr, MotionNotify, PointerMotionMask,
			&mouse_move, &cub);
		mlx_loop(cub.mlx_ptr);
	}
	else
		printf("WRONG INPUT! Try: ./cub3d [PATH TO MAP]\n");
	return (0);
}
