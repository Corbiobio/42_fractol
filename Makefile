.PHONY: all clean fclean re libft mlx run val

NAME = fractol
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE_DIR = include/

C_FILE =	fractol.c\
			utils.c\
			init_data.c\
			key_input.c\
			mouse_input.c\
			verif_param.c

SRC_FILE := $(addprefix $(SRC_DIR), ${C_FILE})

OBJ = $(C_FILE:.c=.o)
OBJ := $(addprefix $(OBJ_DIR), ${OBJ})

LIBFT_NAME = libft.a
LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)$(LIBFT_NAME)

MLX_NAME = libmlx_Linux.a
MLX_DIR = mlx_linux/
MLX_LIB = $(MLX_DIR)$(MLX_NAME)

INC = -I $(INCLUDE_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR)

all: $(NAME)

${NAME}: libft mlx $(OBJ_DIR)
	$(MAKE) .NotRelink

.NotRelink: $(LIBFT_LIB) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(INC) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) -o $(NAME) 
	touch .NotRelink

libft:
	$(MAKE) $(LIB_NAME) -C $(LIBFT_DIR)

mlx:
	$(MAKE) all -C $(MLX_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE_DIR)$(NAME).h Makefile
	$(CC) $(CFLAGS) $(INC) -I/usr/include -Imlx_linux -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) clean
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