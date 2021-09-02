/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 12:17:01 by jng               #+#    #+#             */
/*   Updated: 2021/09/02 12:17:01 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Frees all the mutexes
** 
** @param void
** @return void
*/
void	free_mutexes(void)
{
	int	i;

	i = -1;
	while (++i < g_global.philo_amount)
		pthread_mutex_destroy(&(g_global.fork_mutex[i]));
	pthread_mutex_destroy(&(g_global.print_mutex));
}

/*
** Frees the philo array
** 
** @param t_philo *philos	The philo array to be freed
** @return void
*/
void	free_philos(t_philo *philos)
{
	free(philos);
}
