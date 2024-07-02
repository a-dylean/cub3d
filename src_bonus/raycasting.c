/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:42:01 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/02 09:51:56 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*Gets the x coordinates of the camera + calculates the
ray position and direction, then saves which 'box' of
the map we are in, then get the len of ray from one x
or y-side to the next x or y-side */
static void	populate_ray_struct(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = player->dir_y + player->plane_y * ray->camera_x;
	ray->dir_y = player->dir_x + player->plane_x * ray->camera_x;
	ray->map_x = (int)(player->x);
	ray->map_y = (int)(player->y);
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

/*Calculate distance projected on camera direction (Euclidean distance
will give fisheye effect!)*/
static int	calculate_distance_to_wall(t_ray *ray, t_player *player,
	int east_west)
{
	if (east_west == 0)
		ray->perp_wall_dist = (ray->map_x - player->x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	ray->total_distance += ray->perp_wall_dist;
	return (east_west);
}

/*Digital Differential Analyzer - draws a straight line between 2 given 
points and finds the closest wall that a ray intersects*/
static int	perform_dda_algorithm(t_ray *ray, t_cub *cub)
{
	int	hit_east_west;

	while (true)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			hit_east_west = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			hit_east_west = 1;
		}
		if (cub->map[ray->map_y][ray->map_x] == '1')
			break ;
	}
	return (calculate_distance_to_wall(ray, &cub->player, hit_east_west));
}

/*calculates the initial step direction and distance to
the first side (vertical or horizontal) that the ray will intersect
Checks first if the ray moves to the left or right, then down or up.*/
static void	get_step_and_distance_to_side(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

int	cast_ray(t_cub *cub)
{
	int		wall_orientation;
	t_img	img;

	cub->img = &img;
	cub->img->img_ptr = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img->address = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	cub->img->x = -1;
	while (++cub->img->x < WIDTH)
	{
		cub->ray.total_distance = 0;
		populate_ray_struct(&cub->ray, &cub->player, img.x);
		get_step_and_distance_to_side(&cub->ray, &cub->player);
		wall_orientation = perform_dda_algorithm(&cub->ray, cub);
		get_draw_coordinates(&cub->ray);
		get_wall_texture(&cub->ray, wall_orientation);
		draw_image_into_buffer(cub, &img, &cub->ray, &cub->textures);
	}
	draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, img.img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, img.img_ptr);
	return (0);
}
