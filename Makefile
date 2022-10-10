SRCS		= 	split.c \
				pipex.c \
				utils.c \
				parsing.c

SRCS		:= $(addprefix src/,$(SRCS))

OBJS		= ${SRCS:.c=.o}

NAME		= pipex

CC			= gcc

MAKE		= make

RM			= rm -rf

CFLAGS		= -Wall -Werror -Wextra -Iinclude

$(NAME):	$(OBJS)
			$(CC) ${CFLAGS} -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus