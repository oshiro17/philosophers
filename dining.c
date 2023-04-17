#include "philosophers.h"

t_stat	eat(t_info	*info, t_philo	*philo)
{
	if (philo->id % 2)
		usleep(500);
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->left);
	print_message(philo, FORK);
	usleep(5000000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);

	return(DEFAULT);
}

void	*routine(void *vptr)
{
	t_philo				*philo;
	t_info				*info;
	struct timeval		tv;
	t_stat				stat;

	philo = (t_philo *)vptr;
	info = philo->info;
	stat = DEFAULT;
	pthread_mutex_lock(&info->philo_eat_mutex[philo->id]);
	gettimeofday(&tv, NULL);
	philo->time_last_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	while (1)
	{
		if (stat == DEFAULT)
			stat = eat(info, philo);
	}
	// printf("%d\n",philo->id);
	// printf("%d\n",philo->info->eat_num);

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
	i = 0;
	while (i <info->philo_num)
	{
		pthread_join(info->philo[i].philo_thread, NULL);
		i++;
	}
}