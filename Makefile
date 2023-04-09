SRCS		=	main.c	\
				check_args.c	\
				ft_atol.c	\
				put_error_return.c	\
				# make_pthread.c	\

OBJS		=	$(SRCS:%.c=%.o)

CC			=	cc
# CFLAGS		=	-Wall -Wextra -Werror
NAME		=	philo

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:		
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all