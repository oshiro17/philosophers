/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panti <panti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 02:35:41 by panti             #+#    #+#             */
/*   Updated: 2023/04/30 03:52:31 by panti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_philos_full(t_info	*info)
{
	size_t	full_count;
	size_t	i;

	full_count = 0;
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
	size_t		i;
	size_t		time_last_eat;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_lock(&info->philo_eat_mutex[i]);
		time_last_eat = info->philo[i].time_last_eat;
		pthread_mutex_unlock(&info->philo_eat_mutex[i]);
		if (get_time() - time_last_eat >= info->die_time)
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

	info = (t_info *)vptr;
	while (1)
	{
		action_time(5);
		if (check_philos_full(info))
			return (NULL);
		if (check_philos_dead(info))
			return (NULL);
	}
}
