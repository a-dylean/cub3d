/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:54:55 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/01 14:06:39 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	get_wall_texture(t_ray *ray, int side)
{
	if (side == 0)
	{
		if (ray->dir_x < 0)
			ray->face = WEST;
		else
			ray->face = EAST;
	}
	else
	{
		if (ray->dir_y < 0)
			ray->face = NORTH;
		else
			ray->face = SOUTH;
	}
}

/*Calculate height of line to draw on screen + get lowest
and highest pixel to fill in stripe */
void	get_draw_coordinates(t_ray *ray)
{
	int	line_height;

	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

/*Get the exact position on the wall where the ray hits, then ensure
the value is within 0 and 1*/
double	where_wall_hit(int face, t_cub *cub)
{
	double	wall_x;

	if (face == EAST || face == WEST)
		wall_x = cub->player.y + cub->ray.total_distance * cub->ray.dir_y;
	else
		wall_x = cub->player.x + cub->ray.total_distance * cub->ray.dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	where_x_on_texture(int face, t_cub *cub, double wall_x)
{
	int	texture_x;

	texture_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if ((face == EAST || face == WEST) && cub->ray.dir_x > 0)
		texture_x = TEXTURE_WIDTH - texture_x - 1;
	if ((face == NORTH || face == SOUTH) && cub->ray.dir_y < 0)
		texture_x = TEXTURE_WIDTH - texture_x - 1;
	return (texture_x);
}

void	*get_texture(t_cub *cub, int face)
{
	if (face == NORTH)
		return (cub->textures.img_ptr_north);
	else if (face == SOUTH)
		return (cub->textures.img_ptr_south);
	else if (face == EAST)
		return (cub->textures.img_ptr_east);
	else
		return (cub->textures.img_ptr_west);
}
