.PHONY: all clean fclean re makelib run val

NAME = fractol
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC_FILE =	fractol.c\
			
OBJ = ${SRC_FILE:.c=.o}

LIB_NAME = libft.a
LIB_DIR = libft/

INC = -I . -I ${LIB_DIR}

all: ${NAME}

%.o: %.c 
	${CC} ${CFLAGS} ${INC} -c $< -o $@

${NAME}: ${OBJ} fractol.h
	${MAKE} makelib
	${CC} ${CFLAGS} -g3 ${INC} ${OBJ} ${LIB_NAME} -o ${NAME}

makelib:
	${MAKE} -C ${LIB_DIR}
	cp ${LIB_DIR}${LIB_NAME} ${LIB_NAME}

clean:
	rm -f ${OBJ}

fclean: 
	${MAKE} -C ${LIB_DIR} fclean
	${MAKE} clean
	rm -f ${LIB_NAME}
	rm -f ${NAME}

re:
	${MAKE} fclean
	${MAKE} all

run:
	${MAKE}
	./${NAME}

val:
	${MAKE}
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./${NAME}