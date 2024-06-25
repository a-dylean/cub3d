#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <../mlx/mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Structures */

typedef struct s_img
{
	void			*img;
	char			*address;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_txtr
{
	char			*orientation;
	char			*path;
	struct s_txtr	*next;
}					t_txtr;

typedef struct s_cub
{
	char			**map;
	int				map_height;
	int				map_width;
	t_img			*img;
	t_txtr			*textures;
}					t_cub;

/* Parsing */

void				parse_input(char *path, t_cub *cub);

/* Utils */

void				exit_with_error(char *error);
void				free_and_exit(char *msg, t_cub *cub, char *new_line);
int					valid_format(char *filename);
void				free_map(char **map);
int					get_map_height(char *filename);

/* Textures */
void				add_txtr_back(t_txtr **txtr, t_txtr *new);
t_txtr				*new_txtr(char *orientation, char *path);
#endif