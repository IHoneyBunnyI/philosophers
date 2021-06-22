#include "philo_bonus.h"

void	free_all(t_all *all)
{
	all->philo = 0;
	free(all->philo);
}

void	error(t_all *all, int i)
{
	if (i == 1)
		printf("\033[31;4mERROR: wrong argument\033[0m\n");
	if (i == 2)
		printf("\033[31;4mERROR: malloc\033[0m\n");
	if (i == 3)
		printf("\033[31;4mERROR: start simulation\033[0m\n");
	free_all(all);
	exit(0);
}

int	ft_atoi(char *str)
{
	int		minus;
	long	result;

	minus = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -minus;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + *str - '0';
		str++;
	}
	return (result * minus);
}
