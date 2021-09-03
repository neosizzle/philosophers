/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:02:15 by jng               #+#    #+#             */
/*   Updated: 2021/09/03 14:02:15 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_global	g_global;
t_philo		g_philo;

/*
** Checks for invalid args and prints out usage instructions.
** 
** @param int argc		The argument count
** @return int 			1 if err 0 if good
*/
static int	check_usage(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage : ./philo_bonus [number_of_philosophers]");
		printf(" [time_to_die_ms] [time_to_eat_ms]");
		printf(" [time to sleep_ms]");
		printf(" (optional)[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}

/*
** Initialized the global philo
** 
** @param void	
** @return void
*/
static void	init_g_philo(void)
{
	g_philo.philo_num = 0;
	g_philo.last_time_eaten = 0;
	g_philo.times_eaten = 0;
}

/*
** Initializes all semaphores
** 
** @param void
** @return void
*/
static void	init_sems(void)
{
	int		p_cnt;

	p_cnt = g_global.philo_amount;
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_START);
	sem_unlink(SEM_END);
	g_global.forks = sem_open(SEM_FORKS, O_CREAT, 0660, p_cnt);
	g_global.start = sem_open(SEM_START, O_CREAT, 0660, 0);
	g_global.end = sem_open(SEM_END, O_CREAT, 0660, 0);
}

/*
** Initializes globals
** 
** @param char **argv	The program arguments
** @return void
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
	g_global.simulate = 0;
	init_sems();
}

/*
Entry point
1. Initialize global vars
2. Initialize the global philo
	- Since resources arent shared but duplicated
	In forks, the global philo will get duplicated
	in each child process
3. Initialize processes for every phil
4. If we are in the child process, do the following
	- Wait for stimulation to start
	- Start cycle
	- Join death threads
	- Close sems
5. If we are in parent process
	- Start stimulation
	- Wait for children
	- Free and close everything
*/
int	main(int argc, char *argv[])
{
	int	*child_pids;

	if (check_usage(argc))
		return (1);
	init_globals(argv);
	init_sems();
	init_g_philo();
	child_pids = init_processes();
	if (!child_pids)
	{
		sem_wait(g_global.start);
		philo_cycle();
		pthread_join(g_philo.th_death, NULL);
		pthread_join(g_philo.th_end_handle, NULL);
		close_sems();
	}
	else
	{
		start_cycle();
		wait_children(child_pids);
		free(child_pids);
		close_sems();
	}
	return (0);
}
