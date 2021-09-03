/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 12:17:06 by jng               #+#    #+#             */
/*   Updated: 2021/09/02 12:17:06 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Eat function
** 1. Set last eat time of current philo to curr time
** 2. Print is eating status
** 3. Check for all philos are fed
** 		- if yes, exit_cycle
** 4. Wait for time_to_eat ms
** @param t_thilo *philo	The philo struct pointer
** @return void
*/
void	eat(t_philo *philo)
{
	philo->last_time_eaten = get_time();
	print_status("is eating\n", philo->philo_num);
	pthread_mutex_lock(&(g_global.print_mutex));
	if (++philo->times_eaten >= g_global.times_philo_eat)
		++g_global.philos_fed;
	if (g_global.philos_fed >= g_global.philo_amount)
		end_cycle(philo);
	pthread_mutex_unlock(&(g_global.print_mutex));
	usleep(g_global.time_to_eat * 1000);
}

/*
** Main Thread, where it stimulates grabbing forks,
** sleeping, eating, and thinking
** 
** 1. While stimulation not start, wait.
** 2. Set last eat time to curr time (Assuming they start full)
** 3. Print thinking status (Thinking comes first)
** 4. If the current philo is even, wait 10ms 
** 5. While the stimulation is ongoing, do the following things:
** 		-attempt to take fork 1 mutex (print fork taken if succeed)
** 		-attempt to take fork 2 mutex (print fork taken if succeed)
** 		-call eat function (start eating)
** 		-unlock both forks and start sleeping (print sleeping)
** 		-wake up and think (print thinking)
**		-repeat
** 
** @param void	*arg	Pointer to Philo struct
** @return void	*		Void pointer 
*/
void	*phil_cycle(void *arg)
{
	t_philo	*philo;
	int		p_num;

	philo = (t_philo *)(arg);
	p_num = philo->philo_num;
	while (!g_global.start)
		;
	philo->last_time_eaten = get_time();
	print_status("is thinking\n", philo->philo_num);
	if (philo->philo_num % 2 == 0)
		usleep(10000);
	while (g_global.start)
	{
		pthread_mutex_lock(&(g_global.fork_mutex[philo->fork_one]));
		print_status("has taken a fork\n", p_num);
		pthread_mutex_lock(&(g_global.fork_mutex[philo->fork_two]));
		print_status("has taken a fork\n", p_num);
		eat(philo);
		pthread_mutex_unlock(&(g_global.fork_mutex[philo->fork_one]));
		pthread_mutex_unlock(&(g_global.fork_mutex[philo->fork_two]));
		print_status("is sleeping\n", p_num);
		usleep(g_global.time_to_sleep * 1000);
		print_status("is thinking\n", p_num);
	}
	return (0);
}

/*
** Death Thread, where it keeps track of last time eaten
** and philosophers dying
** 
** 1. While there is no last eat time (stimulation not start), wait.
** 2. While the stimulation is still on going, do the folllowing :
** 		- wait for time_to_die ms long
** 		- get current time
** 		- if the current time >= last_eat_time + time_to_die
** 			-Phil has died, print message and end the stimulation
** 		- if there is only 1 philo (1 fork)
** 			-Phil has died, print message and end the stimulation
** 		- repeat
** @param void	*arg	Pointer to Philo struct
** @return void	*		Void pointer
*/
void	*death_cycle(void *arg)
{
	t_philo	*philo;
	size_t	time_to_die;
	size_t	curr_time;
	int		p_cnt;

	philo = (t_philo *)(arg);
	p_cnt = g_global.philo_amount;
	time_to_die = g_global.time_to_die;
	while (!(philo->last_time_eaten))
		;
	while (g_global.start)
	{
		usleep(time_to_die * 1000);
		curr_time = get_time();
		if (curr_time >= philo->last_time_eaten + time_to_die || p_cnt == 1)
		{
			pthread_mutex_lock(&(g_global.print_mutex));
			if (g_global.start)
				printf("%lu %i %s", get_time(), philo->philo_num, "died\n");
			end_cycle(philo);
			pthread_mutex_unlock(&(g_global.print_mutex));
		}
	}
	return (0);
}

/*
** This function will create the threads needed for each philo
** 
** @param t_philo *philo		The philo struct array
** @param void *(f)(void *)		The function that the thread should run
** @return pthread_t *th_res	The thread array
*/
pthread_t	*create_threads(t_philo *philo, void *(f)(void *))
{
	int			p_cnt;
	int			i;
	pthread_t	*th_res;

	p_cnt = g_global.philo_amount;
	i = -1;
	th_res = (pthread_t *)malloc(sizeof(pthread_t) * p_cnt);
	while (++i < p_cnt)
		pthread_create(&(th_res[i]), NULL, f, (void *)(&(philo[i])));
	return (th_res);
}

/*
** This function will join the threads and free them once they return
** 
** @param pthread_t *th_cycle	The cycle thread array
** @param pthread_t *th_death	The death thread array
** @return void nothing
*/
void	join_threads(pthread_t *th_cycle, pthread_t *th_death)
{
	int	i;
	int	p_cnt;

	i = -1;
	p_cnt = g_global.philo_amount;
	while (++i < p_cnt)
	{
		pthread_join(th_cycle[i], NULL);
		pthread_join(th_death[i], NULL);
	}
	free(th_cycle);
	free(th_death);
}
