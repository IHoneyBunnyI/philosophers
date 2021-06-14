#include "philo_one.h"
#include <stdio.h>
#include <unistd.h>
#define LEFT_FORK &philo->all->forks[philo->left_fork]
#define RIGHT_FORK &philo->all->forks[philo->right_fork]
#define WRITE &philo->all->write

void	sleep_think(t_philo *philo)
{
	philo->state = SLEEPING;
	pthread_mutex_lock(WRITE);
	printf("%lu %d is sleeping\n", my_time() - philo->all->start, philo->id);
	pthread_mutex_unlock(WRITE);
	usleep(philo->all->t_sleep * 1000);
	philo->state = THINKING;
	pthread_mutex_lock(WRITE);
	printf("%lu %d is thinking\n", my_time() - philo->all->start, philo->id);
	pthread_mutex_unlock(WRITE);

}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(LEFT_FORK);
	pthread_mutex_lock(WRITE);
	printf("%lu %d take a left fork\n", my_time() - philo->all->start, philo->id);
	pthread_mutex_unlock(WRITE);
	pthread_mutex_lock(RIGHT_FORK);
	pthread_mutex_lock(WRITE);
	printf("%lu %d take a right fork\n", my_time() - philo->all->start, philo->id);
	pthread_mutex_unlock(WRITE);
	philo->state = EATING;
	pthread_mutex_lock(WRITE);
	printf("%lu %d is eating\n", my_time() - philo->all->start, philo->id);
	pthread_mutex_unlock(WRITE);
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
