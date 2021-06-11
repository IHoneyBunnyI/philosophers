#include "philo_one.h"
#include <stdio.h>

void	*routine(void *this_philo)
{
	t_philo *philo;

	philo = this_philo;
	printf("im %d left: %d right %d\n", philo->id, philo->left_fork, philo->right_fork);
	if (philo->id % 2 == 1)
		philo->state = 0;
	return (0);
}

void				start(t_all *all)
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
