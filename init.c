/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <htam@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:31:19 by htam              #+#    #+#             */
/*   Updated: 2023/04/25 17:49:31 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_option(char **argv, t_table *table)
{
	if (argv[5])
	{
		table->option = true;
		table->min_eat = (int)ft_atol_lite(argv[5]);
	}
	else
	{
		table->option = false;
		table->min_eat = 0;
	}
}

t_table	*build_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(*table));
	if (!table)
		return (NULL);
	table->number_of_philo = (int)ft_atol_lite(argv[1]);
	table->starting_time = get_current_time();
	table->time_to_die = ft_atol_lite(argv[2]);
	table->time_to_eat = ft_atol_lite(argv[3]);
	table->time_to_sleep = ft_atol_lite(argv[4]);
	check_option(argv, table);
	if (table->number_of_philo < 1 || table->time_to_die == -1
		|| table->time_to_eat == -1 || table->time_to_sleep == -1
		|| table->min_eat == -1)
	{
		free(table);
		return (NULL);
	}
	pthread_mutex_init(&table->butler, NULL);
	pthread_mutex_init(&table->maid, NULL);
	table->die = false;
	return (table);
}

t_fork	*craft_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(*fork));
	if (!fork)
		return (NULL);
	fork->taken = false;
	pthread_mutex_init(&fork->mutex, NULL);
	return (fork);
}

void	one_philo(t_table *table, t_philo *philo, int seat)
{
	if (table->number_of_philo > 1)
		philo[0].left = philo[seat - 1].right;
	else
		philo[0].left = NULL;
}

t_philo	*gather_philo(t_table *table)
{
	t_philo	*philo;
	int		seat;

	philo = malloc(sizeof(*philo) * table->number_of_philo);
	if (!philo)
		return (NULL);
	seat = 0;
	while (seat < table->number_of_philo)
	{
		philo[seat].number = seat + 1;
		philo[seat].right = craft_fork();
		if (!philo[seat].right)
			return (NULL);
		if (seat > 0)
			philo[seat].left = philo[seat - 1].right;
		if (table->option == true)
			philo[seat].max_meal = table->min_eat;
		else
			philo[seat].max_meal = 0;
		philo[seat].table = table;
		philo[seat].last_meal = table->starting_time;
		seat++;
	}
	one_philo(table, philo, seat);
	return (philo);
}
