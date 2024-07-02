/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:10:24 by atonkopi          #+#    #+#             */
/*   Updated: 2024/07/02 15:25:54 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <../mlx/mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1020
# define HEIGHT 720
# define TEXTURE_HEIGHT 32
# define TEXTURE_WIDTH 32
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define WHITE 0x00FFFFFF
# define YELLOW 0x00FFFF00
# define NORTH 10
# define SOUTH 11
# define EAST 12
# define WEST 13
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3
# define FIELD_OF_VIEW 0.66
# define SPACES " \t\n\v\f\r"

/* Structures */

typedef struct s_ray
{
	int				face;
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	double			total_distance;
	int				step_x;
	int				step_y;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			delta_camera_x;
}					t_player;

typedef struct s_textures
{
	void			*img_ptr_north;
	void			*img_ptr_south;
	void			*img_ptr_east;
	void			*img_ptr_west;
	int				floor_color;
	int				ceiling_color;
	int				color;
	double			step;
	double			middle_offset;
	double			tex_y;
	int				wrap_adjustor;
}					t_textures;

typedef struct s_img
{
	void			*img_ptr;
	char			*address;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				x;
}					t_img;

typedef struct s_txtr
{
	char			*orientation;
	char			*path;
	struct s_txtr	*next;
}					t_txtr;

typedef struct s_cub
{
	char			**config_info;
	char			**map;
	int				map_height;
	t_img			*img;
	void			*mlx_ptr;
	void			*win_ptr;
	t_txtr			*txtr;
	t_textures		textures;
	t_player		player;
	t_ray			ray;
}					t_cub;

/* Parsing */
void				parsing(char *path, t_cub *cub);
void				validate_map(char **map, int rows, t_cub *cub);
int					empty_or_spaces_only(char *str);
void				set_player(t_cub *cub, t_player *player);

/* Utils */
int					read_file_into_memory(char *path, t_cub *cub);
void				exit_with_error(char *error);
void				free_and_exit(char *msg, t_cub *cub, char *new_line);
int					valid_format(char *filename);
void				free_map(char **map);
int					get_map_height(char **config);
int					array_len(char **array);
void				free_array(char **str);
int					list_len(t_txtr *list);
int					has_duplicates(t_txtr *list);
int					str_is_numeric(char *str);
void				invalid_commas(char *line, char **color_ids, t_cub *cub);
void				init_empty_map(t_cub *cub);
int					map_line(char *line);
int					check_conditions(char **arr, int rows);
void				free_textures(t_txtr *txtr);
void				clean_up(t_cub *cub, char *error);

/* MLX Utils */
int					destroyer(t_cub *cub);
int					key_press(int keycode, t_cub *cub);

/* Textures */
int					is_texture(char *id);
char				*get_path(char *line);
void				parse_texture(char **nodes, t_cub *cub);
void				add_txtr_back(t_txtr **tokens, t_txtr *new_node);
t_txtr				*new_txtr(char *orientation, char *path);
void				textures_errors_check(t_cub *cub);
int					load_textures(t_cub *cub);

/* Colors */
int					is_color(char *id);
void				colors_errors_check(t_cub *cub);
void				parse_color(char *line, t_cub *cub, char **color_ids);
int					get_rgb_int(char **colors);

/* Raycasting */
int					cast_ray(t_cub *cub);

/* Moves & Rotations*/
void				move_player(t_cub *cub, double dir_x, double dir_y);
void				rotate_player(t_cub *cub, double rotation_speed);
int					mouse_move(int x, int y, t_cub *cub);

/* Drawing */
void				draw_image_into_buffer(t_cub *cub, t_img *img, t_ray *ray,
						t_textures *textures);
void				*get_texture(t_cub *cub, int face);
int					where_x_on_texture(int face, t_cub *cub, double wall_x);
double				where_wall_hit(int face, t_cub *cub);
void				get_draw_coordinates(t_ray *ray);
void				get_wall_texture(t_ray *ray, int side);

#endif