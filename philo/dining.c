/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panti <panti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 02:51:26 by panti             #+#    #+#             */
/*   Updated: 2023/05/01 17:06:02 by panti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	}
	pthread_mutex_unlock(&info->mutex_finish);
	return (NULL);
}

void	dining(t_info *info)
{
	size_t		i;

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
