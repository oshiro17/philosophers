#include "philosophers.h"

void	init_philo_utils(t_info	*info, int i, t_philo	*philo)
{
	philo->info = info;
	philo->id = i;
	philo->right = &info->fork_mutex[i];
	if (i == info->philo_num - 1)
		philo->left = &info->fork_mutex[0];
	else
		philo->left = &info->fork_mutex[i + 1];
	philo->full = false;
	philo->cnt_eat = 0;
	return ;
}

bool	init_philo(t_info	*info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		init_philo_utils(info, i, &info->philo[i]);
		i++;
	}
	return (true);
}
