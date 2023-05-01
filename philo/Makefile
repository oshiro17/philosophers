SRCS		=	main.c	\
				check_args.c	\
				ft_atol.c	\
				put_error_return.c	\
				make_mutex.c	\
				init_philo.c \
				dining.c	\
				print_message.c	\
				utils_time.c \
				check_finish.c \
				action.c \
			
OBJS		=	$(SRCS:%.c=%.o)

CC			=	cc
FSANITIZE	=	-g -fsanitize=thread
CFLAGS		=	-Wall -Wextra -Werror $(FSANITIZE)
NAME		=	philo

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:		
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all