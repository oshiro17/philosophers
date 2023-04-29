#include "philosophers.h"

bool	make_mutex(t_info	*info)
{
	size_t	i;

	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_mutex_init(&info->fork_mutex[i], NULL) || \
			pthread_mutex_init(&info->philo_eat_mutex[i], NULL))
			return (put_error_return("Error, mutex_init_error"));
		i++;
	}
	if (pthread_mutex_init(&info->mutex_write, NULL) || \
		pthread_mutex_init(&info->mutex_finish,NULL))
		return (false);
	return (true);
}