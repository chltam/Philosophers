/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <htam@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:27:43 by htam              #+#    #+#             */
/*   Updated: 2023/04/19 22:33:18 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str)
{
	printf("\033[0;31m%s\033[0;39m\n", str);
	return (1);
}

int	valid_input(int argc, char **argv)
{
	int	arg;
	int	c;

	arg = 1;
	if (argc != 5 && argc != 6)
		return (ft_error("invalid number of arguments"));
	while (argv[arg])
	{
		c = 0;
		while (argv[arg][c])
		{
			if (argv[arg][c] < '0' || argv[arg][c] > '9')
				return (ft_error("invalid format of argument"));
			c++;
		}
		arg++;
	}
	return (0);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atol_lite(char *str)
{
	long	rel;

	rel = 0;
	while (*str)
	{
		rel = rel * 10 + *str - '0';
		str++;
		if (rel > 2147483647)
			return (-1);
	}
	return (rel);
}
