#include "../includes/cub3d.h"

/*draw the pixels of the stripe as a vertical line*/
void	draw_vertical_line(t_cub *cub, int x, int y1, int y2, int color)
{
	int	y;
	int	temp;

	temp = 0;
	if (y2 < y1)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x, y, color);
		y++;
	}
}

/*Gets the x coordinates of the camera + calculates the
ray position and direction, then saves which 'box' of
the map we are in, then get the len of ray from one x
or y-side to the next x or y-side */
void	populate_ray_struct(t_ray *ray, t_player *player, int x)
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
int	calculate_distance_to_wall(t_ray *ray, t_player *player, int east_west)
{
	if (east_west == 0)
		ray->perp_wall_dist = (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->dir_y;
	ray->total_distance += ray->perp_wall_dist;
	return (east_west);
}

/*Digital Differential Analyzer - draws a straight line between 2 given 
points and finds the closest wall that a ray intersects*/
int	perform_dda_algorithm(t_ray *ray, t_cub *cub)
{
	int hit_east_west;

	while (true)
	{
		// Jump to next map square, OR in x-direction, OR in y-direction
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
		// Check if ray has hit a wall
		if (cub->map[ray->map_y][ray->map_x] == '1')
			break ;
	}
	return (calculate_distance_to_wall(ray, &cub->player, hit_east_west));
}

/*calculates the initial step direction and distance to
the first side (vertical or horizontal) that the ray will intersect*/
void	get_step_and_distance_to_side(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0) // means that the ray moves to the left
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else // moves to the right
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0) // the ray moves down
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else // the ray moves up
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

/*Calculate height of line to draw on screen + get lowest
and highest pixel to fill in stripe */
void	get_draw_coordinates(t_ray *ray)
{
	int line_height;

	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -line_height / 2 + HEIGHT / 2;
	if(ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + HEIGHT / 2;
	if(ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

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

double	where_wall_hit(int face, t_cub *cub)
{
	double wall_x; // Exact position on the wall where the ray hits

	if (face == EAST || face == WEST)
		wall_x = cub->player.y + cub->ray.total_distance * cub->ray.dir_y;
	else
		wall_x = cub->player.x + cub->ray.total_distance * cub->ray.dir_x;
	wall_x -= floor(wall_x); // Ensure the value is within 0 and 1

	return (wall_x);
}

int where_x_on_texture(int face, t_cub *cub, double wall_x)
{
	int	texture_x;

	texture_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if ((face == EAST || face == WEST) && cub->ray.dir_x > 0)
		texture_x = TEXTURE_WIDTH - texture_x - 1;
	if ((face == NORTH || face == SOUTH) && cub->ray.dir_y < 0)
		texture_x = TEXTURE_WIDTH - texture_x - 1;

	return (texture_x);
}

int	get_pixel(void *img_ptr, int x, int y)
{
    char    *pixel;
    int     color;
	char *data;
	int bpp;
	int size_line;
	int endian;

	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
   // if (x < 0 || y < 0)
     //   return (0); // Return a default color or handle error if coordinates are out of bounds

    // Calculate the address of the pixel
    pixel = data + (y * size_line + x * (bpp / 8));

    // Assuming the color format is ARGB (which is common), extract the color
    color = *(int*)pixel;

    return (color);
}

int set_pixel_color(t_cub *cub, double tex_pos)
{
	double wall_x;
	int texture_x;
	int color;
	int face = cub->ray.face;

	wall_x = where_wall_hit(face, cub);
	texture_x = where_x_on_texture(face, cub, wall_x);
	if (face == NORTH)
		color = get_pixel(cub->textures.img_ptr_north , texture_x, (int)tex_pos & (TEXTURE_WIDTH - 1));
	else if (face == SOUTH)
		color = get_pixel(cub->textures.img_ptr_south , texture_x, (int)tex_pos & (TEXTURE_WIDTH - 1));
	else if (face == EAST)
		color = get_pixel(cub->textures.img_ptr_east , texture_x, (int)tex_pos & (TEXTURE_WIDTH - 1));
	else
		color = get_pixel(cub->textures.img_ptr_west , texture_x, (int)tex_pos & (TEXTURE_WIDTH - 1));
	return (color);
}

void draw_textured_vertical_line(t_cub *cub, int x, int draw_start, int draw_end) 
{
	int y = draw_start;
	double step = 1.0f * TEXTURE_WIDTH / ((int)HEIGHT / cub->ray.total_distance);
	double texture_middle_offset = (TEXTURE_HEIGHT / 2) - (step * (draw_end - draw_start) / 2);
	double tex_y = (texture_middle_offset > 0) ? texture_middle_offset : 0;
	int color;

	draw_vertical_line(cub, x, 0, draw_start, BLUE);
	for (y = draw_start; y < draw_end; y++) {
		int texY = (int)tex_y & (TEXTURE_HEIGHT - 1);
		tex_y += step;
		if (cub->ray.face == NORTH)
			color = get_pixel(cub->textures.img_ptr_north, where_x_on_texture(NORTH, cub, where_wall_hit(NORTH, cub)), texY);
		else if (cub->ray.face == SOUTH)
			color = get_pixel(cub->textures.img_ptr_south, where_x_on_texture(SOUTH, cub, where_wall_hit(SOUTH, cub)), texY);
		else if (cub->ray.face == EAST)
			color = get_pixel(cub->textures.img_ptr_east, where_x_on_texture(EAST, cub, where_wall_hit(EAST, cub)), texY);
		else
			color = get_pixel(cub->textures.img_ptr_west, where_x_on_texture(WEST, cub, where_wall_hit(WEST, cub)), texY);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x, y, color);
	}
	draw_vertical_line(cub, x, draw_end, HEIGHT, WHITE);
}

int cast_ray(t_cub *cub)
{
	int	x;
	int side;//was a NS or a EW wall hit?

	x = -1;
	while (++x < WIDTH)
	{
		cub->ray.total_distance = 0;
		populate_ray_struct(&cub->ray, &cub->player, x);
		get_step_and_distance_to_side(&cub->ray, &cub->player);
		side = perform_dda_algorithm(&cub->ray, cub);
		get_draw_coordinates(&cub->ray);
		get_wall_texture(&cub->ray, side);
		draw_textured_vertical_line(cub, x, cub->ray.draw_start, cub->ray.draw_end);
	}
	return (0);
}
