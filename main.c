#include "philosophers.h"

void	mutex_destroy(t_info	*info)
{
	size_t	i;

	i = 0;
	pthread_mutex_unlock(&info->mutex_write);
	while (i < info->philo_num)
	{
		pthread_mutex_destroy(&info->fork_mutex[i]);
		pthread_mutex_destroy(&info->philo_eat_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&info->mutex_finish);
	pthread_mutex_destroy(&info->mutex_write);
}

int	main(int argc, const char *argv[])
{
	t_info	info;

	// put_initial(&info);
	if (!check_args(argc, argv, &info)||!make_mutex(&info))
		return (1);
	init_philo(&info);
	dining(&info);
	mutex_destroy(&info);
	// make_thread(&data);
	return(0);
}
