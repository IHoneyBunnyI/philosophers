#include "philo_one.h"
#include <stdio.h>
#include <unistd.h>
#define LEFT_FORK &philo->all->forks[philo->left_fork]
#define RIGHT_FORK &philo->all->forks[philo->right_fork]
#define WRITE &philo->all->write

void	sleep_think(t_philo *philo)
{
	philo->state = SLEEPING;
	printf_msg("is sleeping", philo);
	usleep(philo->all->t_sleep * 1000);
	philo->state = THINKING;
	printf_msg("is thinking", philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(LEFT_FORK);
	printf_msg("take a left fork", philo);
	pthread_mutex_lock(RIGHT_FORK);
	printf_msg("take a right fork", philo);
	philo->state = EATING;
	printf_msg("is eating", philo);
	usleep(philo->all->t_eat * 1000);
	pthread_mutex_unlock(LEFT_FORK);
	pthread_mutex_unlock(RIGHT_FORK);
}

void	*start_life(void *this_philo)
{
	t_philo *philo;

	philo = this_philo;
	if ((philo->id & 1) == 0)
		usleep(100);
	while (!philo->all->end)
	{
		eat(philo);
		sleep_think(philo);
		/*printf("id %d\n", philo->id);*/
	}
	return (0);
}
