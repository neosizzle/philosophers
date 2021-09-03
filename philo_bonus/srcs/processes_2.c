/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 13:58:57 by jng               #+#    #+#             */
/*   Updated: 2021/09/03 13:58:57 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
** Turns off stimulation and sets everything to 0
** 
** @param void
** @return void
*/
void	end_cycle(void)
{
	g_global.simulate = 0;
	g_global.time_to_die = 0;
	g_global.time_to_eat = 0;
	g_global.time_to_sleep = 0;
}

/*
** Increments the start semaphore so the chilren can
** consume and start the process
** 
** @param void
** @return void
*/
void	start_cycle(void)
{
	int	i;

	i = -1;
	while (++i < g_global.philo_amount)
		sem_post(g_global.start);
}

/*
** This func will call waitpid on each child process
** 
** @param int *child_pids	Array of pids to wait
** @return void
*/
void	wait_children(int *child_pids)
{
	int	i;

	i = -1;
	while (++i < g_global.philo_amount)
		waitpid(child_pids[i], 0, 0);
}
