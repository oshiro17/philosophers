#include "philosophers.h"

void	make_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_create(&info->philo[i].philo_thread, NULL
			&routine, &data->philo[i]);
		i++;
	}
}