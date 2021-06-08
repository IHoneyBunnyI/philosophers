#include "philo_one.h"

int		valid_arg(char *arg)
{
	int i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
	}
	return (1);
}

void	get_times_eat(t_all *all, int ac, char **av)
{
	if (ac == 6)
	{
		all->times_eat = ft_atoi(av[ac -2]);
		if (all->times_eat == 0)
			error(all, 1);
	}
}

void	get_others_args(t_all *all, char **av)
{
	all->philosophers = ft_atoi(av[0]);
	all->t_die = ft_atoi(av[1]);
	all->t_eat = ft_atoi(av[2]);
	all->t_sleep = ft_atoi(av[3]);
}

int		get_args(t_all *all, int ac, char **av)
{
	int i;

	i = -1;
	while (av[++i])
	{
		if (!valid_arg(av[i]))
			return (0);
	}
	get_times_eat(all, ac, av);
	get_others_args(all, av);
	return (1);
}
