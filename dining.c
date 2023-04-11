#include "philosophers.h"

void	*routine(void *vptr)
{
	t_philo *philo;

	philo = (t_philo *);
	printf("%d\n",philo->id);
	return (NULL);
}

void	dining(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_create(&info->philo[i].philo_thread, NULL, routine, &info->philo[i]);
		i++;
	}
	i = 0;
	while (i <info->philo_num)
	{
		pthread_join(info->philo[i].philo_thread, NULL);
		i++;
	}
}