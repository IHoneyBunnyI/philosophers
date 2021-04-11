#include "philo_one.h"


int		main(int ac, char **av)
{
	t_all all;

	(void)av;
	init_all(&all);
	if (ac < 5 || ac > 6)
		error(&all, 1);
	if (!get_args(&all, ac, av + 1))
		error(&all, 1);
	printf("\033[32mDONE\033[0m\n");
	return 0;
}
