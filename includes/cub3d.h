#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <../mlx/mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Parsing */

void	parse_input(char *path);

/* Utils */

void	exit_with_error(char *error);

#endif