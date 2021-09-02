/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 12:17:03 by jng               #+#    #+#             */
/*   Updated: 2021/09/02 12:17:03 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_global	g_global;

/*
** Prints out usage instructions.
** 
** @param void
** @return void
*/
static void	print_usage(void)
{
	printf("Usage : ./philo [number_of_philosophers]");
	printf(" [time_to_die_ms] [time_to_eat_ms]");
	printf(" [time to sleep_ms]");
	printf(" (optional)[number_of_times_each_philosopher_must_eat]\n");
}

/*
** Init mutexes, 1 mutex for each fork and 1 mutex for printing operations
** 
** @param void
** @return void
*/
static void	init_mutexes(void)
{
	int				i;
	int				phil_cnt;
	pthread_mutex_t	print_mutex;

	phil_cnt = g_global.philo_amount;
	i = -1;
	pthread_mutex_init(&(print_mutex), NULL);
	g_global.print_mutex = print_mutex;
	g_global.fork_mutex = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * phil_cnt);
	while (++i < phil_cnt)
		pthread_mutex_init(&(g_global.fork_mutex[i]), NULL);
}

/*
** Initializes globals
** 
** @param char **argv	The program arguments
** @return void
** TO DO: init mutexes
*/
static void	init_globals(char *argv[])
{
	g_global.philo_amount = ft_atoi(argv[1]);
	g_global.time_to_die = ft_atoi(argv[2]);
	g_global.time_to_eat = ft_atoi(argv[3]);
	g_global.time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		g_global.times_philo_eat = 2147483647;
	else
		g_global.times_philo_eat = ft_atoi(argv[5]);
	g_global.philos_fed = 0;
	init_mutexes();
	g_global.start = 0;
}

/*
** Initializes philo array.
** Mallocs memory for every philo struct based on 
** philo_num
** 
** @param int	p_cnt	The number of philos
** @return t_philo *philos	The philo array
*/
static t_philo	*init_philos(int p_cnt)
{
	t_philo	*res;
	int		i;

	res = (t_philo *)malloc(sizeof(t_philo) * p_cnt);
	i = -1;
	while (++i < p_cnt)
	{
		res[i].philo_num = i + 1;
		res[i].fork_one = i;
		res[i].fork_two = (i + 1) % p_cnt;
		res[i].last_time_eaten = 0;
		res[i].times_eaten = 0;
	}
	return (res);
}

/*
** Entry point.
** 
** 1. Initialize globals
** 2. Initialize philo array
** 3. Initializes mutexes
** 4. Intializes threads
** 5. Start and join threads
** 6. Free everything.
*/
int	main(int argc, char *argv[])
{
	t_philo		*philos;
	pthread_t	*th_cycle;
	pthread_t	*th_death;

	if (argc != 5 && argc != 6)
	{
		print_usage();
		return (1);
	}
	init_globals(argv);
	philos = init_philos(g_global.philo_amount);
	th_cycle = create_threads(philos, &phil_cycle);
	th_death = create_threads(philos, &death_cycle);
	g_global.start = 1;
	join_threads(th_cycle, th_death);
	free_mutexes();
	free_philos(philos);
	return (0);
}
