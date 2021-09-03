/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 13:56:11 by jng               #+#    #+#             */
/*   Updated: 2021/09/03 13:56:11 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

/*
** Closes all opened semaphores
** 
** @param void
** @return void
*/
void	close_sems(void)
{
	sem_close(g_global.forks);
	sem_close(g_global.start);
	sem_close(g_global.end);
}
