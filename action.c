#include "philosophers.h"
void	action_time(size_t action_time)
{
	size_t				start_time;

	start_time = get_time();
	while (get_time() - start_time < action_time)
		usleep(500);
}

t_stat	action_sleep(t_info *info, t_philo	*philo)
{
	print_message(philo, SLEEP);
	action_time(info->sleep_time);
	return (DEFAULT);
}

t_stat	think(t_philo	*philo)
{
	print_message(philo, THINK);
	return (DEFAULT);
}

t_stat	eat(t_info	*info, t_philo	*philo)
{
	if (philo->id % 2)
		usleep(500);
	pthread_mutex_lock(philo->right);
	print_message(philo, FORK);
	if (info->philo_num == 1)
	{
		pthread_mutex_unlock(&info->philo_eat_mutex[philo->id]);
		return (DEAD);
	}
	pthread_mutex_lock(philo->left);
	print_message(philo, FORK);
	pthread_mutex_lock(&info->philo_eat_mutex[philo->id]);
	print_message(philo, EAT);
	philo->time_last_eat = get_time();
	philo->cnt_eat++;
	if (info->must_eat_num < philo->cnt_eat && info->must_eat_num != 0)
		philo->full = true;
	pthread_mutex_unlock(&info->philo_eat_mutex[philo->id]);
	action_time(info->eat_time);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (DEFAULT);
}
