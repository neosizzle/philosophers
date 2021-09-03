/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 12:17:19 by jng               #+#    #+#             */
/*   Updated: 2021/09/02 12:17:19 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

/*
** Global struct
** 
** philo_amount - stores the num of philos / forks (input)
** time_to_die - stores the time for a philo to die (input)
** time_to_eat - stores the time for a philo to eat (input)
** time_to_sleep - stores the time for a philo to sleep (input)
** times_philo_eat - stores the num of times a philo has to eat (input)
** philos_fed - stores the num of philos successfully fed
** fork_mutex - stores the mutext of the forks in an array
** print_mutex - stores the mutext for printing results
**	 and incrementing philos fed
** start - 1 if the stimulation starts and 0 otherwise
*/
typedef struct s_global {
	int				philo_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_philo_eat;
	int				philos_fed;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	int				start;
}				t_global;

/*
** Philo struct (struct of each philosopher)
** 
** philo_num - the number of each philo
** fork_one - the index of the first fork
** fork_two - the index of the second fork
** last_time_eaten - the timestamp of the last time eaten
** times_eaten - the number of how many times a philo has eaten
*/
typedef struct s_philo {
	int		philo_num;
	int		fork_one;
	int		fork_two;
	int		last_time_eaten;
	int		times_eaten;
}	t_philo;

//Global variables
extern t_global	g_global;

//Thread functions
void		*phil_cycle(void *arg);
void		*death_cycle(void *arg);
void		end_cycle(t_philo *philo);
pthread_t	*create_threads(t_philo *philo, void *(f)(void *));
void		join_threads(pthread_t *th_cycle, pthread_t *th_death);

//Free functions
void		free_mutexes(void);
void		free_philos(t_philo *philos);

//Util functions
int			ft_atoi(char *nptr);
size_t		get_time(void);
void		print_status(char *str, int	p_num);
void		ft_usleep(unsigned int n);
void		print_status(char *str, int	p_num);

#endif