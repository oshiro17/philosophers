#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>


typedef struct s_info
{
	long	fork_num;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	long	eat_num;
}	t_info;

long	ft_atol(const char *str);
bool	put_error_return(char *error_message);
int		main(int argc, const char *argv[]);
bool	check_args(int argc, const char **argv, t_info *info);
void	make_pthread();

#endif