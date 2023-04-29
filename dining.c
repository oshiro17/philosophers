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
	if (info->must_eat_num < philo->cnt_eat)
		philo->full = true;
	pthread_mutex_unlock(&info->philo_eat_mutex[philo->id]);
	action_time(info->eat_time);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (DEFAULT);
}

bool	check_philos_full(t_info	*info)
{
	int	full_count;
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_lock(&info->philo_eat_mutex[i]);
		if (info->philo[i].full)
			full_count++;
		pthread_mutex_unlock(&info->philo_eat_mutex[i]);
		if (full_count == info->philo_num)
		{
			pthread_mutex_lock(&info->mutex_finish);
			info->finish = true;
			pthread_mutex_unlock(&info->mutex_finish);
			print_message(&info->philo[0], FULL);
			return (true);
		}
		i++;
	}
	return (false);

}

bool	check_philos_dead(t_info	*info)
{
	int		i;
	size_t	time_last_eat;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_lock(&info->philo_eat_mutex[i]);
		time_last_eat = info->philo[i].time_last_eat;
		pthread_mutex_unlock(&info->philo_eat_mutex[i]);
		if (get_time() - time_last_eat > info->die_time)
		{
			pthread_mutex_lock(&info->mutex_finish);
			info->finish = true;
			pthread_mutex_unlock(&info->mutex_finish);
			print_message(&info->philo[i], DEAD);
			return (true);
		}	
		i++;
	}
	return (false);
}

void	*check_finish(void	*vptr)
{
	t_info		*info;
	int			full_philo;
	int			i;

	info = (t_info *)vptr;
	full_philo = 0;
	while (1)
	{
		action_time(5);
		if (check_philos_full(info))
			return (NULL);
		if (check_philos_dead(info))
			return (NULL);
	}
}

void	*routine(void *vptr)
{
	t_philo			*philo;
	t_info			*info;
	t_stat			stat;

	philo = (t_philo *)vptr;
	info = philo->info;
	stat = DEFAULT;
	pthread_mutex_lock(&info->philo_eat_mutex[philo->id]);
	philo->time_last_eat = get_time();
	pthread_mutex_unlock(&info->philo_eat_mutex[philo->id]);
	pthread_mutex_lock(&info->mutex_finish);
	while (info->finish != true)
	{
		pthread_mutex_unlock(&info->mutex_finish);
		if (stat == DEFAULT)
			stat = eat(info, philo);
		if (stat == DEFAULT)
			stat = action_sleep(info, philo);
		if (stat == DEFAULT)
			stat = think(philo);
		pthread_mutex_lock(&info->mutex_finish);
		usleep(500);
	}
	pthread_mutex_unlock(&info->mutex_finish);
	return (NULL);
}

void	dining(t_info *info)
{
	int			i;
	pthread_t	check_pthread;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_create(&info->philo[i].philo_thread, \
		NULL, routine, &info->philo[i]);
		i++;
	}
	pthread_create(&info->thread_monitor, NULL, check_finish, info);
	pthread_detach(info->thread_monitor);
	i = 0;
	while (i < info->philo_num)
	{
		pthread_join(info->philo[i].philo_thread, NULL);
		i++;
	}
	return ;
}