.PHONY: all clean fclean re libft mlx run val

NAME = fractol
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE_DIR = include/

C_FILE =	fractol.c\

SRC_FILE := $(addprefix $(SRC_DIR), ${C_FILE})

OBJ = $(C_FILE:.c=.o)
OBJ := $(addprefix $(OBJ_DIR), ${OBJ})

LIBFT_NAME = libft.a
LIBFT_DIR = libft/

MLX_NAME = libmlx_Linux.a
MLX_DIR = mlx_linux/

INC = -I $(INCLUDE_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: src/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -I/usr/include -Imlx_linux -c $< -o $@

$(NAME): libft mlx $(OBJ) $(INCLUDE_DIR)$(NAME).h
	$(CC) $(CFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(INC) $(OBJ) $(LIBFT_NAME) $(MLX_NAME) -o $(NAME) 

libft:
	$(MAKE) all -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)$(LIBFT_NAME) $(LIBFT_NAME)

mlx:
	$(MAKE) all -C $(MLX_DIR)
	cp $(MLX_DIR)$(MLX_NAME) $(MLX_NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: 
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) clean
	rm -f $(LIBFT_NAME)
	rm -f $(MLX_NAME)
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

run:
	$(MAKE)
	./$(NAME)

val:
	$(MAKE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME}