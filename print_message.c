/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panti <panti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 02:46:16 by panti             #+#    #+#             */
/*   Updated: 2023/04/30 02:46:44 by panti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, t_stat stat)
{
	size_t				time;
	bool				finish;

	pthread_mutex_lock(&philo->info->mutex_write);
	time = get_time() - philo->info->time_start;
	pthread_mutex_lock(&philo->info->mutex_finish);
	finish = philo->info->finish;
	pthread_mutex_unlock(&philo->info->mutex_finish);
	if (finish == false || stat == FULL || stat == DEAD)
	{
		if (stat == DEAD)
			printf("%10zdms philo%-4d is died\n", time, philo->id + 1);
		if (stat == FULL)
			printf("All philosophers are full\n");
		if (stat == FORK)
			printf("%10zdms philo%d has taken a fork\n", time, philo->id + 1);
		if (stat == EAT)
			printf("%10zdms philo%d is eating\n", time, philo->id + 1);
		if (stat == SLEEP)
			printf("%10zdms philo%d is sleeping\n", time, philo->id + 1);
		if (stat == THINK)
			printf("%10zdms philo%d is thinking\n", time, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->info->mutex_write);
	return ;
}
