#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <mlx.h>

typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_cub;

#endif