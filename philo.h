/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <htam@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:37:36 by htam              #+#    #+#             */
/*   Updated: 2023/04/26 16:12:50 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_fork
{
	bool			taken;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_table
{
	int				number_of_philo;
	long			starting_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	bool			option;
	int				min_eat;
	pthread_mutex_t	butler;
	pthread_mutex_t	maid;
	bool			die;
}	t_table;
/*butler protects printf, maid protects die */

typedef struct s_philo
{
	int			number;
	pthread_t	thread;
	t_fork		*left;
	t_fork		*right;
	int			max_meal;
	long		last_meal;
	t_table		*table;

}	t_philo;

int		ft_error(char *str);
int		valid_input(int argc, char **argv);
long	get_current_time(void);
int		ft_atol_lite(char *str);
t_table	*build_table(char **argv);
t_fork	*craft_fork(void);
t_philo	*gather_philo(t_table *table);
int		die_in_sleep(t_philo *philo);
void	*action_v4(void *info);
int		ft_ms_sleep_v2(long ms, t_philo *philo);
int		print_action(t_philo *philo, char *str);
void	*starve_to_die(t_philo *philo);
#endif