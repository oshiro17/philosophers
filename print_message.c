#include "philosophers.h"

void	print_message(t_philo *philo, t_stat stat)
{
	size_t				time;
	bool				finish;

	pthread_mutex_lock(&philo->info->mutex_write);
	time = get_time() - philo->info->time_start;
	pthread_mutex_lock(&philo->info->mutex_finish);
	finish = philo->info->finish;
	pthread_mutex_unlock(&philo->info->mutex_finish);
	if (finish == false || stat == FULL || stat == DEAD)
	{
		if (stat == DEAD)
			printf("%10zdms =>   philo_%-4d is died\n", time, philo->id);
		if (stat == FULL)
			printf("All philosophers are full\n");
		if (stat == FORK)
			printf("%10zdms => philo%d has taken a fork\n", time, philo->id);
		if (stat == EAT)
			printf("%10zdms => philo%d is eating\n", time, philo->id);
		if (stat == SLEEP)
			printf("%10zdms => philo%d is sleeping\n", time, philo->id);
		if (stat == THINK)
			printf("%10zdms => philo%d is thinking\n", time, philo->id);
	}
	pthread_mutex_unlock(&philo->info->mutex_write);
	return ;
}