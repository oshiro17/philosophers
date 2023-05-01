/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panti <panti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 02:54:12 by panti             #+#    #+#             */
/*   Updated: 2023/04/30 02:54:21 by panti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_overlong(long ret, int sign, char c)
{
	long	tmp;

	tmp = LONG_MIN / 10;
	if (sign == -1)
		c++;
	if (ret < tmp || (ret == tmp && LONG_MAX % 10 + 1 < c - '0'))
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	ret;

	ret = 0;
	sign = -1;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (is_overlong(ret, sign, *str) && sign == -1)
			return (put_error_return("Argument is larger than long_max"));
		if (is_overlong(ret, sign, *str) && sign == 1)
			return (LONG_MIN);
		ret = (ret * 10) - ((int)*str - '0');
		str++;
	}
	return (ret * sign);
}
