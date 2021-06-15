#include "philo_one.h"

void	free_all(t_all *all)
{
	(void)all;
}

void	error(t_all *all, int i)
{
	if (i == 1)
		printf("\033[31;4mERROR: wrong argument\033[0m\n");
	if (i == 2)
		printf("\033[31;4mERROR: malloc\033[0m\n");
	if (i == 3)
		printf("\033[31;4mERROR: WWWWWWWWWWWWWW\033[0m\n");
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

unsigned long	my_time()
{
	struct timeval	t_time;

	gettimeofday(&t_time, 0);
	return ((t_time.tv_sec * 1000) + (t_time.tv_usec / 1000));
}

void	printf_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(WRITE);
	printf("%lu %d %s\n", my_time() - philo->all->start, philo->id, msg);
	pthread_mutex_unlock(WRITE);
}
