#include "philo.h"

/*
** Frees all the mutexes
** 
** @param void
** @return void
*/
void	free_mutexes()
{
	int	i;

	i = -1;
	while (++i < g_global.philo_amount)
		pthread_mutex_destroy(&(g_global.fork_mutex[i]));
	pthread_mutex_destroy(&(g_global.print_mutex));
}

void	free_philos()
{

}