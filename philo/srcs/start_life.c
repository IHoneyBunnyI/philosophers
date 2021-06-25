#include "philo_one.h"

void	ft_usleep(unsigned long ms_sec)
{
	unsigned long	start;

	start = my_time();
	while (my_time() - start < ms_sec)
		usleep(500);
}

void	*check_life(void *this_philo)
{
	t_philo			*p;
	pthread_mutex_t	*write;

	p = this_philo;
	write = &p->all->write;
	while (!p->all->end)
	{
		if (p->all->done_eat == p->all->philosophers_number)
		{
			pthread_mutex_lock(write);
			p->all->end = 1;
		}
		if (my_time() > p->time_of_death && p->state != EATING && !p->all->end)
		{
			pthread_mutex_lock(write);
			p->all->end = 1;
			printf("%lu %d died\n", my_time() - p->all->start, p->id);
		}
	}
	pthread_mutex_unlock(&p->all->end_mutex);
	return (0);
}

void	eat_slepp_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->forks[philo->left_fork]);
	printf_msg("has taken a fork", philo);
	pthread_mutex_lock(&philo->all->forks[philo->right_fork]);
	printf_msg("has taken a fork", philo);
	philo->time_of_death = my_time() + philo->all->t_die;
	philo->state = EATING;
	philo->times_eat++;
	if (philo->times_eat == philo->all->parsed_times_eat)
		philo->all->done_eat++;
	printf_msg("is eating", philo);
	ft_usleep(philo->all->t_eat);
	pthread_mutex_unlock(&philo->all->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->all->forks[philo->right_fork]);
	philo->state = SLEEPING;
	printf_msg("is sleeping", philo);
	ft_usleep(philo->all->t_sleep);
	philo->state = THINKING;
	printf_msg("is thinking", philo);
}

void	*start_life(void *this_philo)
{
	t_philo		*philo;
	pthread_t	th;

	philo = this_philo;
	if ((philo->id & 1) == 0)
		usleep(500);
	philo->time_of_death = my_time() + philo->all->t_die;
	pthread_create(&th, 0, check_life, philo);
	pthread_detach(th);
	while (!philo->all->end)
		eat_slepp_think(philo);
	return (0);
}
