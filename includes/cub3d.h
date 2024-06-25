#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <mlx.h>

typedef struct s_textures
{
	void	*img_ptr_north;
	void	*img_ptr_south;
	void	*img_ptr_east;
	void	*img_ptr_west;	
}	t_textures;

typedef struct s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_height; // to fill after parsing
	int			win_width; // to fill after parsing
	t_textures	textures;
}	t_cub;

#endif