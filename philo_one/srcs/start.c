#include "philo_one.h"

unsigned long		my_time()
{
	struct timeval	t_time;

	gettimeofday(&t_time, 0);
	return ((t_time.tv_sec * 1000) + (t_time.tv_usec / 10000));
}

void				start(t_all *all)
{
	unsigned long start = my_time();
	while (1)
	{
		printf("%lu\n", my_time() - start);
		//printf("%ld\n", t_time.tv_sec);
	}
	(void)all;
}
