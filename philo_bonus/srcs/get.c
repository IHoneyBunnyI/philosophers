#include "philo_bonus.h"

int	valid_arg(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
	}
	return (1);
}

int	get_args(t_all *all, int ac, char **av)
{
	int	i;

	i = -1;
	while (av[++i])
	{
		if (!valid_arg(av[i]))
			return (0);
	}
	if (ac == 6)
	{
		all->parsed_times_eat = ft_atoi(av[ac - 2]);
		if (all->parsed_times_eat == 0)
			error(all, 1);
	}
	all->philosophers_number = ft_atoi(av[0]);
	all->t_die = ft_atoi(av[1]);
	all->t_eat = ft_atoi(av[2]);
	all->t_sleep = ft_atoi(av[3]);
	return (1);
}
