#include "philo_one.h"

void	init_all(t_all *all)
{
	all->philosophers_number = 0;
	all->t_die = 0;
	all->t_eat = 0;
	all->t_sleep = 0;
	all->times_eat = -1;
	all->start = 0;
	all->philo = 0;
}

void	init_forks(t_all *all)
{
	int i;

	i = -1;
	all->forks = malloc(sizeof(pthread_mutex_t) * all->philosophers_number);
	if (!all->forks)
		error(all, 2);
	while (++i < all->philosophers_number)
		pthread_mutex_init(&all->forks[i], 0);
}

void	init_philos_forks(t_all *all)
{
	int i;

	i = -1;
	all->philo = malloc(sizeof(t_philo) * all->philosophers_number);
	if (!all->philo)
		error(all, 2);
	while (++i < all->philosophers_number)
	{
		if (i == all->philosophers_number - 1)
		{
			all->philo[i].left_fork = i;
			all->philo[i].right_fork = 0;
		}
		else 
		{
			all->philo[i].left_fork = i;
			all->philo[i].right_fork = i + 1;
		}
		all->philo[i].all = all;
		all->philo[i].state = THINKING;
		all->philo[i].id = i + 1;
		all->philo[i].eat_times = 0;
	}
	init_forks(all);
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
	init_philos_forks(&all);
	start(&all);
	return 0;
}
