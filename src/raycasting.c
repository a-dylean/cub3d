#include "cub3d.h"

void verLine(void *mlx_ptr, void *win_ptr, int x, int y1, int y2, int color)
{
    int y;

    if (y2 < y1)
    {
        int temp = y1;
        y1 = y2;
        y2 = temp;
    }

    y = y1;
    while (y <= y2)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
        y++;
    }
}
int cast_ray(t_cub *cub)
{
    for (int x = 0; x < WIDTH; x++)
    {
        // Calculate ray position and direction
        cub->ray.camera_x = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
        cub->ray.dir_x = cub->player.dir_y + cub->player.plane_y * cub->ray.camera_x;
        cub->ray.dir_y = cub->player.dir_x + cub->player.plane_x * cub->ray.camera_x;
        
        // Which box of the map we're in
        cub->ray.map_x = (int)(cub->player.x);
        cub->ray.map_y = (int)(cub->player.y);
        
        // Length of ray from one x or y-side to next x or y-side
        cub->ray.delta_dist_x = fabs(1 / cub->ray.dir_x);
        cub->ray.delta_dist_y = fabs(1 / cub->ray.dir_y);
        
        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?
        
        // Calculate step and initial sideDist
        if (cub->ray.dir_x < 0)
        {
            cub->ray.step_x = -1;
            cub->ray.side_dist_x = (cub->player.x - cub->ray.map_x) * cub->ray.delta_dist_x;
        }
        else
        {
            cub->ray.step_x = 1;
            cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->player.x) * cub->ray.delta_dist_x;
        }
        if (cub->ray.dir_y < 0)
        {
            cub->ray.step_y = -1;
            cub->ray.side_dist_y = (cub->player.y - cub->ray.map_y) * cub->ray.delta_dist_y;
        }
        else
        {
            cub->ray.step_y = 1;
            cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->player.y) * cub->ray.delta_dist_y;
        }
        
        // Perform DDA
        while (hit == 0)
        {
            // Jump to next map square, OR in x-direction, OR in y-direction
            if (cub->ray.side_dist_x < cub->ray.side_dist_y)
            {
                cub->ray.side_dist_x += cub->ray.delta_dist_x;
                cub->ray.map_x += cub->ray.step_x;
                side = 0;
            }
            else
            {
                cub->ray.side_dist_y += cub->ray.delta_dist_y;
                cub->ray.map_y += cub->ray.step_y;
                side = 1;
            }
            // Check if ray has hit a wall
			if (cub->map[cub->ray.map_y][cub->ray.map_x] != '0') hit = 1;
        }
        
        // Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0) cub->ray.perp_wall_dist = (cub->ray.map_x - cub->player.x + (1 - cub->ray.step_x) / 2) / cub->ray.dir_x;
        else           cub->ray.perp_wall_dist = (cub->ray.map_y - cub->player.y + (1 - cub->ray.step_y) / 2) / cub->ray.dir_y;
        
        // Calculate height of line to draw on screen
        int lineHeight = (int)(HEIGHT / cub->ray.perp_wall_dist);
        
        //calculate lowest and highest pixel to fill in current stripe
        cub->ray.draw_start = -lineHeight / 2 + HEIGHT / 2;
        if(cub->ray.draw_start < 0)cub->ray.draw_start = 0;
        cub->ray.draw_end = lineHeight / 2 + HEIGHT / 2;
        if(cub->ray.draw_end >= HEIGHT)cub->ray.draw_end = HEIGHT - 1;
        
        //choose wall color
        int color;
        if (side == 0) // NS wall
        {
            if (cub->ray.dir_x < 0)
                color = RED; // West wall
            else
                color = GREEN; // East wall
        }
        else // EW wall
        {
            if (cub->ray.dir_y < 0)
                color = BLUE; // North wall
            else
                color = WHITE; // South wall
        }
            
        //draw the pixels of the stripe as a vertical line
		verLine(cub->mlx_ptr, cub->win_ptr, x, 0, cub->ray.draw_start, WHITE); // modify the color of the floor to use the color from the map parsing
        verLine(cub->mlx_ptr, cub->win_ptr, x, cub->ray.draw_start, cub->ray.draw_end, color);
		verLine(cub->mlx_ptr, cub->win_ptr, x, cub->ray.draw_end, HEIGHT, YELLOW);
    }
	return (0);
}