/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <htam@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:02:30 by htam              #+#    #+#             */
/*   Updated: 2023/04/26 16:57:22 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_fork_state(t_philo *philo, bool state)
{
	pthread_mutex_lock(&philo->right->mutex);
	philo->right->taken = state;
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_lock(&philo->left->mutex);
	philo->left->taken = state;
	pthread_mutex_unlock(&philo->left->mutex);
}

int	eat_sleep_think(t_philo *philo)
{
	set_fork_state(philo, true);
	philo->last_meal = get_current_time();
	if (print_action(philo, "has taken a fork(right)")
		|| print_action(philo, "has taken a fork(left)")
		|| print_action(philo, "is eating"))
		return (1);
	if (ft_ms_sleep_v2(philo->table->time_to_eat, philo))
		return (1);
	set_fork_state(philo, false);
	philo->max_meal--;
	if (philo->max_meal == 0)
	{
		print_action(philo, "has paid the bill");
		return (1);
	}
	if (print_action(philo, "is sleeping"))
		return (1);
	if (ft_ms_sleep_v2(philo->table->time_to_sleep, philo))
		return (1);
	if (print_action(philo, "is thinking"))
		return (1);
	return (0);
}

void	*action_v4(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	while (get_current_time() - philo->last_meal < philo->table->time_to_die)
	{
		if (!philo->left)
			continue ;
		pthread_mutex_lock(&philo->right->mutex);
		if (philo->right->taken == false)
		{
			pthread_mutex_unlock(&philo->right->mutex);
			pthread_mutex_lock(&philo->left->mutex);
			if (philo->left->taken == false)
			{
				pthread_mutex_unlock(&philo->left->mutex);
				if (eat_sleep_think(philo))
					return (NULL);
			}
			else
				pthread_mutex_unlock(&philo->left->mutex);
		}
		else
			pthread_mutex_unlock(&philo->right->mutex);
	}
	return (starve_to_die(philo));
}
