/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panti <panti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 02:36:06 by panti             #+#    #+#             */
/*   Updated: 2023/04/30 02:36:07 by panti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo_utils(t_info	*info, size_t i, t_philo	*philo)
{
	info->time_start = get_time();
	philo->info = info;
	philo->id = i;
	philo->full = false;
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
	size_t	i;

	i = 0;
	while (i < info->philo_num)
	{
		init_philo_utils(info, i, &info->philo[i]);
		i++;
	}
	return (true);
}
