/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 12:17:11 by jng               #+#    #+#             */
/*   Updated: 2021/09/02 12:17:11 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Converts a string to integer
** 
** @param char *nptr	The string to be converted
** @return int res		The converted int result
*/
int	ft_atoi(char *nptr)
{
	size_t	offset;
	int		res;
	int		sign;

	offset = 0;
	res = 0;
	sign = 1;
	while (nptr[offset] == ' ' || nptr[offset] == '\n' || nptr[offset] == '\t'
		|| nptr[offset] == '\r' || nptr[offset] == '\v' || nptr[offset] == '\f')
		offset++;
	if (nptr[offset] == '-' || nptr[offset] == '+')
	{
		if (nptr[offset] == '-')
			sign = -1;
		offset++;
	}
	while (nptr[offset] >= '0' && nptr[offset] <= '9')
		res = res * 10 + (nptr[offset++] - '0');
	return (res * sign);
}

/*
** Gives the time in format xy
** x - seconds
** y - miliseconds
** 
** @param void
** @return size_t time	The time in format specified above
*/
size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (size_t)1000
			+ (time.tv_usec / 1000)) % 1000000);
}

/*
** Resets every global variable and turns off start
** 
** @param t_philo *philo	Pointer to philo struct
** @return void
*/
void	end_cycle(t_philo *philo)
{
	g_global.start = 0;
	g_global.time_to_die = 0;
	g_global.time_to_eat = 0;
	g_global.time_to_sleep = 0;
	pthread_mutex_unlock(&(g_global.fork_mutex[philo->fork_one]));
	pthread_mutex_unlock(&(g_global.fork_mutex[philo->fork_two]));
}

/*
** Prints out status in the format of
** [timestamp] [p_num] [status]
** 
** @param char *str	The message to be printed
** @param int			The philosophers number
** @return void
*/
void	print_status(char *str, int	p_num)
{
	pthread_mutex_lock(&(g_global.print_mutex));
	if (g_global.start)
		printf("%lu %i %s", get_time(), p_num, str);
	pthread_mutex_unlock(&(g_global.print_mutex));
}

/*
** Custom usleep function that sleeps for n microseconds
** Default usleep is unprecise 
** 
** @param unsigned int n	Microseconds to sleep
** @return void
*/
void	ft_usleep(unsigned int n)
{
	struct timeval	begin;
	struct timeval	temp;

	gettimeofday(&begin, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&temp, NULL);
		if ((size_t)(((size_t)(temp.tv_sec - begin.tv_sec)) * 1000000 +
				((size_t)(temp.tv_usec - begin.tv_usec))) > n)
			break ;
	}
}
