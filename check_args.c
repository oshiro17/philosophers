/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panti <panti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 02:39:25 by panti             #+#    #+#             */
/*   Updated: 2023/04/30 02:48:31 by panti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_num(const char *num)
{
	int	i;

	i = 0;
	if (num[0] == '+' && num[1])
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	check_num(const char *num)
{
	if (is_num(num))
	{
		if (ft_atol(num) <= INT_MAX)
			return ((int)ft_atol(num));
	}
	return (0);
}

bool	check_args(int argc, char const **argv, t_info *info)
{
	if (argc < 5)
		return (put_error_return("Error, too few argument"));
	if (argc > 6)
		return (put_error_return("Error, too many argument"));
	info->philo_num = check_num(argv[1]);
	info->die_time = check_num(argv[2]);
	info->eat_time = check_num(argv[3]);
	info->sleep_time = check_num(argv[4]);
	if (argc == 6)
		info->must_eat_num = check_num(argv[5]);
	else
		info->must_eat_num = 0;
	if (!info->philo_num || !info->die_time || !info->eat_time
		|| !info->sleep_time || (!info->must_eat_num && argc == 6)
		|| info->philo_num > 200)
		return (put_error_return("Error, arguments is invalid"));
	return (true);
}
