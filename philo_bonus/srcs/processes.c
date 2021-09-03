/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 13:59:20 by jng               #+#    #+#             */
/*   Updated: 2021/09/03 13:59:20 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
** Death thread function that detects death events
** 
** 1. Get the time to die 
** 2. While the phil havent had first meal, wait
** 3. While the stimulation is ongoing fo the collowing
** 	- Wait for time_to_die ms
** 	- Get the current time
** 	- If the current time >= last_eat_time + time_to_die
** 	- Phil has died, print message
** 	- End cycle and post to end semaphore
** 	- Release forks and break
** 
** @param void *arg	void pointer
** @return NULL
*/
void	*death_cycle(void *arg)
{
	size_t	die_time;
	size_t	curr_time;

	(void)arg;
	die_time = g_global.time_to_die;
	while (!g_philo.last_time_eaten)
		;
	while (g_global.simulate)
	{
		usleep(die_time * 1000);
		curr_time = get_time();
		if (curr_time >= (die_time + g_philo.last_time_eaten))
		{
			print_status("has died\n", g_philo.philo_num);
			sem_post(g_global.end);
			end_cycle();
			sem_post(g_global.forks);
			sem_post(g_global.forks);
			break ;
		}
	}
	return (0);
}

/*
** end handler thread, detects death or full event
** and ends own philo cycle when death or full is detected
** 
** @param void *arg	void pointer
** @return NULL
*/
void	*end_handle(void *arg)
{
	(void)arg;
	sem_wait(g_global.end);
	end_cycle();
	sem_post(g_global.end);
	return (0);
}

/*
** Spins up child processes for every phil
** as well as create death threads for child process
** 
** @param void
** @return NULL if in child process, the array of child pids 
** 	for parent process
*/
int	*init_processes(void)
{
	int	*child_pids;
	int	pid;
	int	i;

	child_pids = (int *)malloc(sizeof(int) * g_global.philo_amount);
	i = -1;
	while (++i < g_global.philo_amount)
	{
		g_philo.philo_num = i + 1;
		pid = fork();
		if (!pid)
			break ;
		child_pids[i] = pid;
	}
	if (pid)
		return (child_pids);
	free(child_pids);
	pthread_create(&(g_philo.th_death), NULL, &death_cycle, NULL);
	pthread_create(&(g_philo.th_end_handle), NULL, &end_handle, NULL);
	return (0);
}

/*
** Eat process
** 
** 1. Determines if times eaten is equal to the number of each philo has to eat
** 2. If yes, end the current philo cycle
** 3. Increments times eaten, updates last time eaten
**	 and prints status wait for time_to_eat ms
** 
** @param void
** @return void
*/
static void	eat(void)
{
	if (g_philo.times_eaten == g_global.times_philo_eat)
	{
		end_cycle();
		sem_post(g_global.end);
	}
	g_philo.times_eaten++;
	g_philo.last_time_eaten = get_time();
	print_status("is eating\n", g_philo.philo_num);
	usleep(g_global.time_to_eat * 1000);
}

/*
** Main philo cycle, simulating eating thinking and sleeping
** 
** 1. Enable the simulate switch
** 2. Set last eat time to curr time (Starting full)
** 3. Start thinking
** 4. While the simulation is ongoing, do the following
** 	- Attempt to grab 1 fork (sem_wait / print is success)
** 	- Attempt to grab 1 more fork (sem_wait / print is success)
** 	- Start eating
** 	- Put down 2 forks (sem_post x2)
** 	- Start sleeping for time_to_sleep ms (print status)
** 	- Wake up and start thinking  (print status)
** 	- Repeat
** 
** @param void
** @return void
*/
void	philo_cycle(void)
{
	int	p_num;

	p_num = g_philo.philo_num;
	g_global.simulate = 1;
	g_philo.last_time_eaten = get_time();
	print_status("is thinking\n", p_num);
	if (p_num % 2 == 0)
		usleep(10000);
	while (g_global.simulate)
	{
		sem_wait(g_global.forks);
		print_status("has taken a fork\n", p_num);
		sem_wait(g_global.forks);
		print_status("has taken a fork\n", p_num);
		eat();
		sem_post(g_global.forks);
		sem_post(g_global.forks);
		print_status("is sleeping\n", p_num);
		usleep(g_global.time_to_sleep * 1000);
		print_status("is thinking\n", p_num);
	}
}
