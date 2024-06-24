NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC

INCLUDES = -I includes -Ilibft -Imlx

SRC = 	src/main.c\

OBJ_DIR = obj
OBJ := $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))

LIBFT = libft/libft.a
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L $(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) -L libft -lft $(MLX_FLAGS)

$(LIBFT):
	make -C libft

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	make clean -C libft
	make clean -C $(MLX_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re