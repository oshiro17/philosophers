#include "philosophers.h"

void initial_philo(t_info *info, int i)
{
		info->philo[i].philo_id = info;
		info->philo[i].philo_id = i;
		info->philo[i].eat_num = info->eat_num;
		if(i < info->philo_num - 1)
			info->philo[i].right = &info->philo[i + 1].left;
		else
			info->philo[info->philo_num - 1].right = &info->philo[0].left;
}

void make_mutex(t_info	*info)
{
	int i;

	i = 0;
	while (i < info->philo_num)
	{
		initial_philo(info, i);
		pthread_mutex_init(&info->philo[i].left);
	}
	return ;
}