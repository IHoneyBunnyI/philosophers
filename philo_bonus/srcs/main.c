#include "philo_bonus.h"

void	init_all(t_all *all)
{
	all->philosophers_number = 0;
	all->t_die = 0;
	all->t_eat = 0;
	all->t_sleep = 0;
	all->parsed_times_eat = -1;
	all->start = 0;
	all->philo = 0;
	all->end = 0;
	all->done_eat = 0;
}

int		main(int ac, char **av)
{
	t_all	all;
	int	i;

	i = -1;
	init_all(&all);
	if (ac < 5 || ac > 6)
		error(&all, 1);
	if (!get_args(&all, ac, av + 1))
		error(&all, 1);
	return 0;
}
