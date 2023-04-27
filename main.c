/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <htam@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:46:22 by htam              #+#    #+#             */
/*   Updated: 2023/04/26 17:38:07 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_the_room(t_table *table, t_philo *philo)
{
	int	n;

	n = 0;
	while (n < table->number_of_philo)
	{
		pthread_mutex_destroy(&philo[n].right->mutex);
		free(philo[n].right);
		n++;
	}
	pthread_mutex_destroy(&table->butler);
	pthread_mutex_destroy(&table->maid);
	free(philo);
	free(table);
}

int	create_and_join(t_table *table, t_philo *philo)
{
	int	n;

	n = 0;
	while (n < table->number_of_philo)
	{
		if (pthread_create(&philo[n].thread, NULL,
				action_v4, (void *)&philo[n]))
			return (ft_error("pthread create failed"));
		n++;
	}
	while (n > 0)
	{
		if (pthread_join(philo[n - 1].thread, NULL))
			return (ft_error("pthread join failed"));
		n--;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo	*philo;

	if (valid_input(argc, argv) == 1)
		return (0);
	table = build_table(argv);
	if (!table)
		return (ft_error("ERROR"));
	philo = gather_philo(table);
	if (!philo)
		return (ft_error("ERROR"));
	create_and_join(table, philo);
	free_the_room(table, philo);
	return (0);
}
