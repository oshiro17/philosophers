#include "philosophers.h"

void	action_time(size_t action_time)
{
	struct timeval		tv;
	size_t				start_time;

	gettimeofday(&tv, NULL);
	start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	while ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_time < action_time)
	{
		usleep(500);
		gettimeofday(&tv, NULL);
	}
}

t_stat	eat(t_info	*info, t_philo	*philo)
{
	struct timeval		tv;

	if (philo->id % 2)
		usleep(500);
	pthread_mutex_lock(philo->right);
	print_message(philo, FORK);
	pthread_mutex_lock(philo->left);
	print_message(philo, FORK);
	pthread_mutex_lock(&info->philo_eat_mutex[philo->id]);
	print_message(philo, EAT);
	gettimeofday(&tv, NULL);
	philo->time_last_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	philo->cnt_eat++;
	if (info->must_eat_num < philo->cnt_eat)
		philo->full =  true;
	pthread_mutex_unlock(&info->philo_eat_mutex[philo->id]);
	action_time(info->eat_time);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (DEFAULT);
}

// void	ft_sleep(size_t	sleep)
// {
// 	size_t				start;
// 	struct timeval		tv;


// 	start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
// 	while (get_time() - start < sleep)
// 		usleep(500);
// }


void	*check_finish(void	*vptr)
{
	t_info		*info;
	int			full_philo;
	int			i;

	info = (t_info *)vptr;
	full_philo = 0;
	while (1)
	{
		full_philo = 0;
		action_time(5);
		// usleep(500);
		i = 0;
		while (i < info->philo_num)
		{
			pthread_mutex_lock(&info->philo_eat_mutex[i]);
			if (info->philo[i].full == true)
				full_philo++;
			if (full_philo == info->philo_num)
			{
				pthread_mutex_lock(&info->mutex_finish);
				info->finish = true;
				pthread_mutex_unlock(&info->mutex_finish);
				print_message(&info->philo[0], FULL);
				return (NULL);
			}
			pthread_mutex_unlock(&info->philo_eat_mutex[i]);
			i++;
		}
	}
}

void	*routine(void *vptr)
{
	t_philo			*philo;
	t_info			*info;
	struct timeval	tv;
	t_stat			stat;

	philo = (t_philo *)vptr;
	info = philo->info;
	stat = DEFAULT;
	pthread_mutex_lock(&info->philo_eat_mutex[philo->id]);
	gettimeofday(&tv, NULL);
	philo->time_last_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	pthread_mutex_unlock(&info->philo_eat_mutex[philo->id]);
	pthread_mutex_lock(&info->mutex_finish);
	while (info->finish != true)
	{
		pthread_mutex_unlock(&info->mutex_finish);
		if (stat == DEFAULT)
			stat = eat(info, philo);
		usleep(500);
		pthread_mutex_lock(&info->mutex_finish);
	}
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
	printf("129aaaaaaaaaaaaaaaa:%zd\n",info->philo_num);
	pthread_create(&info->thread_monitor, NULL, check_finish, info);
	pthread_detach(info->thread_monitor);
	i = 0;
	while (i < info->philo_num)
	{
		pthread_join(info->philo[i].philo_thread, NULL);
		i++;
	}
}