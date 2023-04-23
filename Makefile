SRCS		=	main.c	\
				check_args.c	\
				ft_atol.c	\
				put_error_return.c	\
				make_mutex.c	\
				init_philo.c \
				dining.c	\
				print_message.c	\
			
OBJS		=	$(SRCS:%.c=%.o)

CC			=	cc
# CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		=	-g -fsanitize=thread
NAME		=	philo

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:		
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all