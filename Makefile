NAME = fractol
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -flto -g3 -march=native

#__directory__
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/

#__src__
SRC_FILES = \
	fractol.c\
	utils.c\
	init_data.c\
	key_input.c\
	mouse_input.c\
	verif_param.c\
	draw_fractal.c\
	take_screenshot.c\
	fractal/mandelbrot.c\
	fractal/julia.c\
	fractal/phoenix.c\
	fractal/burning_ship.c\
	fractal/the_fish.c\
	fractal/weird_mandelbrot.c\
	color/color.c\
	color/color_set_1.c\
	color/color_set_2.c\
	color/color_set_3.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

#__obj__
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

#__dependence__
DEP = $(OBJ:.o=.d)

#__lib__
LIBFT_NAME = libft.a
LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)$(LIBFT_NAME)

MLX_NAME = libmlx_Linux.a
MLX_DIR = mlx_linux/
MLX_LIB = $(MLX_DIR)$(MLX_NAME)
MLX_FLAG = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11

#__include__
INC = -I $(INC_DIR) -I $(LIBFT_DIR)include/ -I $(MLX_DIR)

#__rules__
all: libft mlx $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(MLX_FLAG) -lm $(OBJ) $(LIBFT_LIB) $(MLX_LIB) -o $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

libft:
	$(MAKE) -C $(LIBFT_DIR)

mlx:
	$(MAKE) -C $(MLX_DIR)

img_generator: libft img_generator.c libattopng.c
	$(CC) $(CFLAGS) -lm img_generator.c libattopng.c $(INC) $(LIBFT_LIB) -o img_generator

benchmark:
	$(MAKE)
	valgrind --tool=cachegrind --cachegrind-out-file=bench ./$(NAME) mandelbrot
	callgrind_annotate bench > benchmark
	rm bench

#__cleaning__
clean:
	rm -rf $(OBJ_DIR)

fclean:
	rm -rf $(OBJ_DIR) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

-include $(DEP)

.PHONY: all clean fclean re libft mlx img_generator benchmark
