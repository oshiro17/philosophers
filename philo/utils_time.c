/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panti <panti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 02:36:38 by panti             #+#    #+#             */
/*   Updated: 2023/05/01 20:44:45 by panti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	// printf("_______sec:%ld\n",tv.tv_sec);
	// printf("_______use:%d\n",tv.tv_usec);
	// printf("______%ld\n",tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
