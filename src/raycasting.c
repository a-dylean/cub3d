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
        double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
        double rayDirX = cub->player.dir_y + cub->player.plane_y * cameraX;
        double rayDirY = cub->player.dir_x + cub->player.plane_x * cameraX;
        
        // Which box of the map we're in
        int mapX = (int)(cub->player.x);
        int mapY = (int)(cub->player.y);
        
        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;
        
        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;
        
        // What direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;
        
        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?
        
        // Calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (cub->player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - cub->player.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (cub->player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - cub->player.y) * deltaDistY;
        }
        
        // Perform DDA
        while (hit == 0)
        {
            // Jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall
			if (cub->map[mapY][mapX] != '0') hit = 1;
        }
        
        // Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0) perpWallDist = (mapX - cub->player.x + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - cub->player.y + (1 - stepY) / 2) / rayDirY;
        
        // Calculate height of line to draw on screen
        int lineHeight = (int)(HEIGHT / perpWallDist);
        
        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;
        
        //choose wall color
        int color;
        if (side == 0) // NS wall
        {
            if (rayDirX < 0)
                color = RED; // West wall
            else
                color = GREEN; // East wall
        }
        else // EW wall
        {
            if (rayDirY < 0)
                color = BLUE; // North wall
            else
                color = WHITE; // South wall
        }
            
        //draw the pixels of the stripe as a vertical line
		verLine(cub->mlx_ptr, cub->win_ptr, x, 0, drawStart, WHITE);
        verLine(cub->mlx_ptr, cub->win_ptr, x, drawStart, drawEnd, color);
		verLine(cub->mlx_ptr, cub->win_ptr, x, drawEnd, HEIGHT, YELLOW);
    }
	return (0);
}