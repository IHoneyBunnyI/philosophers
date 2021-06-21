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
	while (!philo->all->end)
	{
		if (philo->all->done_eat == philo->all->philosophers_number)
		{
			pthread_mutex_lock(&philo->all->write);
			philo->all->end = 1;
		}
		if (my_time() > philo->time_of_death && philo->state != EATING && !philo->all->end)
		{
			if (pthread_mutex_lock(WRITE) == 0)
			{
				philo->all->end = 1;
				printf("%lu %d died\n", my_time() - philo->all->start, philo->id);
			}
			return (0);
		}
		usleep(500);
	}
	pthread_mutex_unlock(&philo->all->end_mutex);
	return (0);
}

void	eat_slepp_think(t_philo *philo)
{
	if (!philo->all->end)
	{
		pthread_mutex_lock(LEFT_FORK);
		printf_msg("has taken a fork", philo);
		pthread_mutex_lock(RIGHT_FORK);
		printf_msg("has taken a fork", philo);
	}
	philo->time_of_death = my_time() + philo->all->t_die;
	philo->state = EATING;
	philo->times_eat++;
	if (philo->times_eat == philo->all->parsed_times_eat)
		philo->all->done_eat++;
	if (!philo->all->end)
		printf_msg("is eating", philo);
	ft_usleep(philo->all->t_eat);
	pthread_mutex_unlock(LEFT_FORK);
	pthread_mutex_unlock(RIGHT_FORK);
	philo->state = SLEEPING;
	if (!philo->all->end)
		printf_msg("is sleeping", philo);
	ft_usleep(philo->all->t_sleep);
	philo->state = THINKING;
	if (!philo->all->end)
		printf_msg("is thinking", philo);
}

void	*start_life(void *this_philo)
{
	t_philo *philo;
	pthread_t th;

	philo = this_philo;
	if ((philo->id & 1) == 0)
		usleep(500);
	philo->time_of_death = my_time() + philo->all->t_die;
	pthread_create(&th, 0, check_life, philo);
	pthread_detach(th);
	while (!philo->all->end)
		eat_slepp_think(philo);
	return (0);
}
