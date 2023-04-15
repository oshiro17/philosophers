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

typedef struct s_philo
{
	struct s_info		*info;
	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
	pthread_t			philo_thread;
	int					id;
	bool				full;
	int					cnt_eat;
}	t_philo;

typedef struct s_info
{
	int					philo_num;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					eat_num;
	pthread_mutex_t		fork_mutex[200];
	pthread_mutex_t		philo_eat_mutex[200];
	pthread_mutex_t		write_exit_mtx;
	pthread_mutex_t		mutex_finish;
	// pthread_t			thread_monitor;
	t_philo				philo[200];
}	t_info;

bool	init_philo(t_info	*info);
long	ft_atol(const char *str);
bool	put_error_return(char *error_message);
int		main(int argc, const char *argv[]);
bool	check_args(int argc, const char **argv, t_info *info);
bool	make_mutex(t_info *info);
void	dining(t_info *info);
//void	make_thread(t_info *info);
bool	put_error_return(char *error_message);
bool	init_philo(t_info	*info);
#endif