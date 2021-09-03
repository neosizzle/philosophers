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
This func will call waitpid on each child process
*/
void	wait_children(int *child_pids)
{
	int	i;

	i = -1;
	while (++i < g_global.philo_amount)
		waitpid(child_pids[i], 0, 0);
}
