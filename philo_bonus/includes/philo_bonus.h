/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 13:56:05 by jng               #+#    #+#             */
/*   Updated: 2021/09/03 13:56:05 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>

//Semaphore Macros
# define SEM_FORKS "sem_forks"
# define SEM_START "sem_start"
# define SEM_END "sem_end"

/*
** Global struct
** 
** philo_amount - stores the num of philos / forks (input)
** time_to_die - stores the time for a philo to die (input)
** time_to_eat - stores the time for a philo to eat (input)
** time_to_sleep - stores the time for a philo to sleep (input)
** times_philo_eat - stores the num of times a philo has to eat (input)
** philos_fed - stores the num of philos successfully fed
** simulate - stores the stimulation status
** forks - stores the semaphore for forks
** start - stores the semaphore for start status
** end - stores the semaphore for end status
*/
typedef struct s_global {
	int		philo_amount;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_philo_eat;
	int		philos_fed;
	int		simulate;
	sem_t	*forks;
	sem_t	*start;
	sem_t	*end;
}				t_global;

/*
** Philo struct (struct of each philosopher)
** 
** philo_num - the number of each philo
** last_time_eaten - the timestamp of the last time eaten
** times_eaten - the number of how many times a philo has eaten
** th_death - the thread for death cycle 
** th_death_handle - the thread for death handler 
*/
typedef struct s_philo {
	int			philo_num;
	int			last_time_eaten;
	int			times_eaten;
	pthread_t	th_death;
	pthread_t	th_end_handle;
}	t_philo;

//Global variables
extern t_global	g_global;
extern t_philo	g_philo;

//Processes functions
int		*init_processes(void);
void	wait_children(int *child_pids);
void	*death_cycle(void *arg);
void	*end_handle(void *arg);
void	philo_cycle(void);

//Free functions
void	close_sems(void);

//Util functions
int		ft_atoi(char *nptr);
size_t	get_time(void);
void	end_cycle(void);
void	start_cycle(void);
void	print_status(char *str, int	p_num);

#endif