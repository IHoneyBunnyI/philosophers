#include "philo_one.h"
#include <stdio.h>

void	*routine(void *this_philo)
{
	t_philo *philo;

	philo = this_philo;
	return (0);
}

void				start(t_all *p)
{
	pthread_t th;
	int	i;

	p->start = my_time();
	while (++i < p->philosophers)
	{
		pthread_create(&th, 0, &routine, &p->philo[i]);
		usleep(100);
	}
	pthread_detach(th);
}
