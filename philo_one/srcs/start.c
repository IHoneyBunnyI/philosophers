#include "philo_one.h"

void	start(t_all *all)
{
	struct timeval	t_time;

	while (1)
	{
		gettimeofday(&t_time, 0);
		printf("%d\n", t_time.tv_usec);
		break;
		//printf("%ld\n", t_time.tv_sec);
	}
	(void)all;
}
