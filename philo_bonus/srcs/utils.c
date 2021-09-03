/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 13:58:53 by jng               #+#    #+#             */
/*   Updated: 2021/09/03 13:58:53 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
** Prints out status in the format of
** [timestamp] [p_num] [status]
** 
** @param char *str	The message to be printed
** @param int			The philosophers number
** @return void
*/
void	print_status(char *str, int	p_num)
{
	if (g_global.simulate)
		printf("%lu %i %s", get_time(), p_num, str);
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
