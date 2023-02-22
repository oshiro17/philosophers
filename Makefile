SRCS		=	main.c	\
				check_args.c	\
				ft_atol.c	\
				put_error_return.c	\

OBJS		=	$(SRCS:%.c=%.o)

CC			=	cc
# CFLAGS		=	-Wall -Wextra -Werror
NAME		=	philosophers

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:		
			make fclean
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all