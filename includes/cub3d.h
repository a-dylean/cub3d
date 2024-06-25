#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <mlx.h>

typedef struct s_player // everything is declared as double, math functions take them as parameters
{
	double	x; 		/*initial x position*/
	double	y; 		/*initial y position*/
	double	dir_x; 	/*initial direction x*/
	double	dir_y; 	/*initial direction y*/
	double	plane_x;/* Camera plane X*/
	double	plane_y;/* Camera plane Y*/
}	t_player;

typedef struct s_textures
{
	void	*img_ptr_north;
	void	*img_ptr_south;
	void	*img_ptr_east;
	void	*img_ptr_west;
	int		floor_color;
	int		ceiling_color;
}	t_textures;

typedef struct s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_height;	// to fill after parsing
	int			win_width;	// to fill after parsing
	t_textures	textures;
	t_player	player;		// to fill after parsing
}	t_cub;

#endif