#include "philo_one.h"
#include <stdio.h>

void	*routine(void *this_philo)
{
	t_philo *philo;

	philo = this_philo;
	int i = 0;
	while (i < 10)
	{
		printf(" pthread %d %d\n", philo->id, i);
		usleep(1);
		i++;
	}
	return 0;
}

void				start(t_all *p)
{
	pthread_t th;
	int	i;

	i = -1;
	while (++i < p->philosophers)
		p->philo[i].id = i + 1;
	p->start = my_time();
	i = -1;
	while (++i < p->philosophers)
	{
		pthread_create(&th, 0, &routine, &p->philo[i]);
		usleep(100);
	}
	pthread_detach(th);
}
