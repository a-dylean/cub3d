#include "cub3d.h"

void	set_direction_and_camera(t_cub *cub, t_player *player, int i, int j)
{
	if (cub->map[i][j] == 'N')
	{
		player->dir_x = -1;
		player->plane_y = 0.66; //66 degrees angle POV
	}
	else if (cub->map[i][j] == 'S')
	{
		player->dir_x = 1;
		player->plane_y = -0.66;
	}
	else if (cub->map[i][j] == 'W')
	{
		player->dir_y = -1;
		player->plane_x = -0.66;
	}
	else if (cub->map[i][j] == 'E')
	{
		player->dir_y = 1;
		player->plane_x = 0.66;
	}
}
/*Sets the original position and orientation + camera view of the player after the map is parsed*/
void	set_player(t_cub *cub, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' || cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
			{
				player->x = (double)j + 0.5; // Center the player in the middle of the block, see if needed
				player->y = (double)i + 0.5;
				set_direction_and_camera(cub, player, i, j);
				return ;
			}
			j++;
		}
		i++;
	}

}