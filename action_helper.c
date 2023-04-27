/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <htam@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:05:48 by htam              #+#    #+#             */
/*   Updated: 2023/04/26 16:09:33 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die_in_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->maid);
	if (philo->table->die == true)
	{
		pthread_mutex_unlock(&philo->table->maid);
		return (1);
	}
	philo->table->die = true;
	pthread_mutex_unlock(&philo->table->maid);
	pthread_mutex_lock(&philo->table->butler);
	printf("%ld philo %d died 2\n",
		get_current_time() - philo->table->starting_time, philo->number);
	pthread_mutex_unlock(&philo->table->butler);
	return (1);
}

int	ft_ms_sleep_v2(long ms, t_philo *philo)
{
	long	start;

	start = get_current_time();
	while (get_current_time() < start + ms)
	{
		if (get_current_time() > philo->last_meal + philo->table->time_to_die)
			return (die_in_sleep(philo));
		pthread_mutex_lock(&philo->table->maid);
		if (philo->table->die == true)
		{
			pthread_mutex_unlock(&philo->table->maid);
			return (1);
		}
		pthread_mutex_unlock(&philo->table->maid);
	}
	return (0);
}

int	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->butler);
	pthread_mutex_lock(&philo->table->maid);
	if (philo->table->die == true)
	{
		pthread_mutex_unlock(&philo->table->maid);
		pthread_mutex_unlock(&philo->table->butler);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->maid);
	printf("%ld philo %d %s\n",
		get_current_time() - philo->table->starting_time, philo->number, str);
	pthread_mutex_unlock(&philo->table->butler);
	return (0);
}

void	*starve_to_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->maid);
	if (philo->table->die == true)
	{
		pthread_mutex_unlock(&philo->table->maid);
		return (NULL);
	}
	else
	{
		philo->table->die = true;
		pthread_mutex_unlock(&philo->table->maid);
		pthread_mutex_lock(&philo->table->butler);
		printf("%ld philo %d died\n",
			get_current_time() - philo->table->starting_time, philo->number);
		pthread_mutex_unlock(&philo->table->butler);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->table->maid);
	return (NULL);
}
