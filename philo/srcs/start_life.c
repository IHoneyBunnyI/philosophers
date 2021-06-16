#include "philo_one.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define LEFT_FORK &philo->all->forks[philo->left_fork]
#define RIGHT_FORK &philo->all->forks[philo->right_fork]
#define WRITE &philo->all->write

void	ft_usleep(unsigned long ms_sec)
{
	unsigned long start;

	start = my_time();
	while (my_time() - start < ms_sec)
		usleep(500);
}

void	*check_life(void *this_philo)
{
	t_philo *philo;

	philo = this_philo;
	/*printf("%d\n", philo->all->parsed_times_eat);*/
	while (!philo->all->end)
	{
		if (philo->times_eat == philo->all->parsed_times_eat)
			philo->all->end = 1;
		if (!philo->all->end && philo->state != EATING && my_time() > philo->time_of_death)
		{
			philo->all->end = 1;
			pthread_mutex_lock(&philo->all->write);
			printf("%lu %d died\n", my_time() - philo->all->start, philo->id);
			pthread_mutex_unlock(&philo->all->write);
		}
		usleep(500);
	}
	return (0);
}

void	eat_slepp_think(t_philo *philo)
{
	pthread_mutex_lock(LEFT_FORK);
	printf_msg("take a left fork", philo);
	pthread_mutex_lock(RIGHT_FORK);
	printf_msg("take a right fork", philo);
	philo->time_of_death = my_time() + philo->all->t_die;
	philo->state = EATING;
	philo->times_eat++;
	printf_msg("is eating", philo);
	ft_usleep(philo->all->t_eat);
	pthread_mutex_unlock(LEFT_FORK);
	pthread_mutex_unlock(RIGHT_FORK);
	philo->state = SLEEPING;
	printf_msg("is sleeping", philo);
	ft_usleep(philo->all->t_sleep);
	philo->state = THINKING;
	printf_msg("is thinking", philo);
}

void	*start_life(void *this_philo)
{
	t_philo *philo;

	philo = this_philo;
	pthread_t th;

	pthread_create(&th, 0, check_life, philo);
	/*pthread_detach(th);*/
	philo->time_of_death = my_time() + philo->all->t_die;
	if ((philo->id & 1) == 0)
		usleep(500);
	while (!philo->all->end)
		eat_slepp_think(philo);
	return (0);
}
