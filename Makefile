NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -fPIC

INCLUDES = -I includes -I libft -I mlx
LIBFT = libft/libft.a

SRC = src/clean_up.c src/draw_utils.c src/draw.c src/load_textures.c src/main.c src/mlx_utils.c \
	src/move_and_rotate.c src/parsing_colors_utils.c src/parsing_colors.c src/parsing_file.c \
	src/parsing_map_checks.c src/parsing_map.c src/parsing_textures.c src/parsing.c src/player.c \
	src/raycasting.c src/utils_array.c src/utils_ll.c src/utils.c \

SRC_BONUS = src_bonus/clean_up.c src_bonus/draw_utils.c src_bonus/draw.c src_bonus/load_textures.c \
	src_bonus/main.c src_bonus/minimap.c src_bonus/mlx_utils.c src_bonus/move_and_rotate.c \
	src_bonus/parsing_colors_utils.c src_bonus/parsing_colors.c src_bonus/parsing_file.c \
	src_bonus/parsing_map_checks.c src_bonus/parsing_map.c src_bonus/parsing_textures.c \
	src_bonus/parsing.c src_bonus/player.c src_bonus/raycasting.c src_bonus/utils_array.c \
	src_bonus/utils_ll.c src_bonus/utils.c \

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L $(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) -L libft -lft $(MLX_FLAGS)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(MLX_LIB) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME_BONUS) $(OBJ_BONUS) -L libft -lft $(MLX_FLAGS)

$(LIBFT):
	make -C libft

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	make clean -C libft
	make clean -C $(MLX_DIR)
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus