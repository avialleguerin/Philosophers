/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:24:47 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/27 16:17:27 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_elapsed_time(long timestamp_start)
{
	return (get_time() - timestamp_start);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(t_rules *rules, long ms)
{
	long	start_time;

	start_time = get_time();
	(void)rules;
	while ((get_time() - start_time) < ms)
		usleep(100);
}
