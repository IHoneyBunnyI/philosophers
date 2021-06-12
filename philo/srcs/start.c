#include "philo_one.h"
#include <stdio.h>

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->all->forks[philo->right_fork]);
}

void	*routine(void *this_philo)
{
	t_philo *philo;

	philo = this_philo;
	/*printf("im %d left: %d right %d\n", philo->id, philo->left_fork, philo->right_fork);*/
	if (philo->id % 2 == 0)
		;
	while (!philo->all->end)
	{
		eat(philo);
	}
	return (0);
}

void	start(t_all *all)
{
	pthread_t th;
	int	i;

	i = -1;
	all->start = my_time();
	while (++i < all->philosophers_number)
	{
		pthread_create(&th, 0, &routine, &all->philo[i]);
		usleep(100);
	}
	pthread_detach(th);
}
