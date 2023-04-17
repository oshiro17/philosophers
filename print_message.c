#include "philosophers.h"

t_stat	print_message(t_philo *philo, t_stat stat)
{
	struct timeval		tv;
	size_t				time;

	pthread_mutex_lock(&philo->info->write_mtx);
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->time_last_eat;
	if (stat == FORK)
		printf("%zdms => philo%d has taken a fork\n", time, philo->id + 1);
	pthread_mutex_unlock(&philo->info->write_mtx);
	return (FORK);
}