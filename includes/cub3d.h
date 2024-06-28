#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <../mlx/mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>

#define WIDTH 1020
#define HEIGHT 720
#define TEXTURE_HEIGHT 64
#define TEXTURE_WIDTH 64
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define WHITE 0x00FFFFFF
#define YELLOW 0x00FFFF00
#define NORTH 10
#define SOUTH 11
#define EAST 12
#define WEST 13
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
/* Structures */

typedef struct s_ray
{
	int		face; // What direction is the wall (NO, SO, EA, WE)
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x; // Length of ray from current position to next x or y-side
	double	side_dist_y;
	double	delta_dist_x; // What direction to step in x or y-direction (either +1 or -1)
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player // everything is declared as double, math functions take them as parameters
{
	double	x; 		/*initial x position*/
	double	y; 		/*initial y position*/
	double	dir_x; 	/*initial direction x*/
	double	dir_y; 	/*initial direction y*/
	double	plane_x;/* Camera plane X*/
	double	plane_y;/* Camera plane Y*/
	double	delta_camera_x;
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
	t_ray			ray;	
}					t_cub;

/* Parsing */

void				parse_input(char *path, t_cub *cub);
void				set_player(t_cub *cub, t_player *player);

/* Utils */

void				exit_with_error(char *error);
void				free_and_exit(char *msg, t_cub *cub, char *new_line);
int					valid_format(char *filename);
void				free_map(char **map);
int					get_map_height(char *filename);

/* MLX Utils */
int					destroyer(t_cub *cub);
int					key_press(int keycode, t_cub *cub);	

/* Textures */
void				add_txtr_back(t_txtr **txtr, t_txtr *new);
t_txtr				*new_txtr(char *orientation, char *path);

/* Raycasting */
int 				cast_ray(t_cub *cub);

/* Moves */
void				move_player(t_cub *cub, double dir_x, double dir_y);
void				move_forward(t_cub *cub);
void				move_backward(t_cub *cub);
void				move_left(t_cub *cub);
void				move_right(t_cub *cub);

/* Rotations */
void				rotate_player(t_cub *cub, double rotation_speed);
int					mouse_move(int x, int y, t_cub *cub);

#endif