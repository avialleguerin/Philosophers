/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:16 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/16 17:22:27 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_rules *rules, char *str, int id)
{
	long	time;

	handle_mutex(&rules->write_lock, LOCK);
	time = get_time() - rules->start_time;
	if (!dead_loop(rules))
		printf(GREEN"%ld %d %s\n"RESET, time, id, str);
	handle_mutex(&rules->write_lock, UNLOCK);
}

void	think(t_rules *rules, t_philo *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (pre_sim == false)
		print_message(rules, "is_thinking", philo->id);
	if (rules->philo_nbr % 2 == 0)
		return ;
	t_eat = rules->time_to_eat;
	t_sleep = rules->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_sleep(rules, t_think * 0.10);
}

void	dream(t_rules *rules, t_philo *philos)
{
	print_message(rules, "is_sleeping", philos->id);
	precise_sleep(rules, rules->dead_flag);
}

void	eat(t_philo *philo)
{
	handle_mutex(philo->first_fork, LOCK);
	handle_mutex(philo->second_fork, LOCK);
	print_message(philo->rules, "has taken a fork", philo->id);
	print_message(philo->rules, "has taken a fork", philo->id);
	philo->meals_eaten++;
	set_mtx_long(&philo->philo_lock, &philo->last_meal, get_time());
	print_message(philo->rules, "is_eating", philo->id);
	precise_sleep(philo->rules, philo->rules->time_to_eat);
	if (philo->meals_eaten == philo->rules->max_meals)
		set_mtx_bool(&philo->philo_lock, &philo->is_full, true);
	handle_mutex(philo->first_fork, UNLOCK);
	handle_mutex(philo->second_fork, UNLOCK);
}
