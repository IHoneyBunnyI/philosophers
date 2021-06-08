#include "philo_one.h"

void	init_all(t_all *all)
{
	all->philosophers = 0;
	all->t_die = 0;
	all->t_eat = 0;
	all->t_sleep = 0;
	all->times_eat = -1;
	all->start = 0;
	all->philo = 0;
}


int		main(int ac, char **av)
{
	t_all all;
	int i;

	i = -1;
	init_all(&all);
	if (ac < 5 || ac > 6)
		error(&all, 1);
	if (!get_args(&all, ac, av + 1))
		error(&all, 1);
	all.philo = malloc(sizeof(t_philo) * all.philosophers);
	if (!all.philo)
		error(&all, 2);
	i = -1;
	while (++i < all.philosophers)
		all.philo[i].id = i + 1;
	all.forks = malloc(sizeof(pthread_mutex_t) * all.philosophers);
	if (!all.forks)
		error(&all, 2);
	i = -1;
	while (++i < all.philosophers)
		pthread_mutex_init(&all.forks[i], 0);
	start(&all);
	return 0;
}
