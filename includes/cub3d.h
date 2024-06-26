#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <../mlx/mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

# define SPACES " \t\n\v\f\r"

/* Structures */

typedef struct s_player // everything is declared as double, math functions take them as parameters
{
	double x;       /*initial x position*/
	double y;       /*initial y position*/
	double dir_x;   /*initial direction x*/
	double dir_y;   /*initial direction y*/
	double plane_x; /* Camera plane X*/
	double plane_y; /* Camera plane Y*/
}					t_player;

typedef struct s_textures
{
	void			*img_ptr_north;
	void			*img_ptr_south;
	void			*img_ptr_east;
	void			*img_ptr_west;
	int				floor_color;
	int				ceiling_color;
}					t_textures;

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
	void			*mlx_ptr;
	void			*win_ptr;
	t_txtr			*txtr;
	t_textures		textures;
	t_player		player;
}					t_cub;

/* Parsing */

void				parse_input(char *path, t_cub *cub);

/* Utils */

void				exit_with_error(char *error);
void				free_and_exit(char *msg, t_cub *cub, char *new_line);
int					valid_format(char *filename);
void				free_map(char **map);
int					get_map_height(char *filename);
int					array_len(char **array);
void free_array(char **str);
int list_len(t_txtr *list);
int has_duplicates(t_txtr *list);

/* Textures */
int is_texture(char *id);
char *get_path(char *line);
void parse_texture(char **nodes, t_cub *cub);
void	add_txtr_back(t_txtr **tokens, t_txtr *new_node);
t_txtr				*new_txtr(char *orientation, char *path);
void textures_errors_check(t_cub *cub);

/* Colors */
int is_color(char *id);
void parse_color(char **nodes, t_cub *cub);
int str_to_color(char *str);

#endif