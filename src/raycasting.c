#include "cub3d.h"

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
		if (cub->map[ray->map_y][ray->map_x] != '0')
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

int	get_wall_texture(t_ray *ray, int side)
{
	if (side == 0) // NS wall
	{
		if (ray->dir_x < 0)
			return RED; // West wall
		else
			return BLUE; // East wall
	}
	else // EW wall
	{
		if (ray->dir_y < 0)
			return GREEN; // North wall
		else
			return WHITE; // South wall
	}
}

int cast_ray(t_cub *cub)
{
	int	x;
	int side;//was a NS or a EW wall hit?
	int color;

	x = -1;
	while (++x < WIDTH)
	{
		populate_ray_struct(&cub->ray, &cub->player, x);
		get_step_and_distance_to_side(&cub->ray, &cub->player);
		side = perform_dda_algorithm(&cub->ray, cub);
		get_draw_coordinates(&cub->ray);
		color = get_wall_texture(&cub->ray, side);		
		draw_vertical_line(cub, x, 0, cub->ray.draw_start, WHITE); // modify the color of the floor to use the color from the map parsing
		draw_vertical_line(cub, x, cub->ray.draw_start, cub->ray.draw_end, color);
		draw_vertical_line(cub, x, cub->ray.draw_end, HEIGHT, YELLOW);
	}
	return (0);
}
