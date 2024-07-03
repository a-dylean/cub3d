/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:52:26 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/03 09:25:53 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	int	pos;

	pos = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(int *)(img->address + pos) = color;
}

static int	get_pixel(void *img_ptr, int x, int y)
{
	char	*pixel;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;

	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	if (x < 0 || y < 0)
		return (0);
	pixel = data + (y * size_line + x * (bpp / 8));
	return (*(int *)pixel);
}

/*draw the pixels of the stripe as a vertical line*/
static void	draw_floor_and_ceiling(t_img *img, int draw_start,
	int draw_end, t_textures *textures)
{
	int	i;

	i = 0;
	while (i <= draw_start)
	{
		draw_pixel(img, img->x, i, textures->ceiling_color);
		i++;
	}
	while (draw_end <= HEIGHT)
	{
		draw_pixel(img, img->x, draw_end, textures->floor_color);
		draw_end++;
	}
}

/*Renders a vertical slice of the wall, along with the ceiling and floor into 
a buffer, by moving through the texture vertically and scaling
it correctly depending on the player's distance to the wall*/
void	draw_image_into_buffer(t_cub *cub, t_img *img,
	t_ray *ray, t_textures *textures)
{
	int	y;

	textures->step = 1.0f * TEXTURE_WIDTH / ((int)HEIGHT / ray->total_distance);
	textures->middle_offset = (TEXTURE_HEIGHT / 2)
		- (textures->step * (ray->draw_end - ray->draw_start) / 2);
	if (textures->middle_offset < 0)
		textures->middle_offset = 0;
	else
		textures->tex_y = textures->middle_offset;
	y = ray->draw_start;
	draw_floor_and_ceiling(img, ray->draw_start, ray->draw_end, textures);
	while (y < ray->draw_end)
	{
		textures->wrap_adjustor = (int)textures->tex_y & (TEXTURE_HEIGHT - 1);
		textures->tex_y += textures->step;
		textures->color = get_pixel(get_texture(cub, ray->face),
				where_x_on_texture(ray->face, cub,
					where_wall_hit(ray->face, cub)), textures->wrap_adjustor);
		draw_pixel(img, img->x, y, textures->color);
		y++;
	}
}
