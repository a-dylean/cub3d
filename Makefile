NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
INCLUDES = -I includes -I libft -I mlx
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L $(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) -L libft -lft $(MLX_FLAGS)

$(LIBFT):
	make -C libft

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	make clean -C libft
	make clean -C $(MLX_DIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re