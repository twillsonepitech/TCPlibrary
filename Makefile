##
## EPITECH PROJECT, 2022
## MyFtp
## File description:
## Makefile
##

CC	=	gcc

CFLAGS	+=	-I./include
CFLAGS	+=	-W -Wextra -Werror

RM	?=	rm -rf

SRCS	=	main.c				\

OBJS	=	${SRCS:.c=.o}

NAME	=	myftp

all:	${NAME}

${NAME}:	${OBJS}
	${CC} -o ${NAME} ${OBJS} ${CFLAGS}

clean:
	${RM} ${OBJS}
	${RM} *.gc*

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
