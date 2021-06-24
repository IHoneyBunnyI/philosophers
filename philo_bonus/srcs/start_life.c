#include "philo_bonus.h"

void	ft_usleep(unsigned long ms_sec)
{
	unsigned long start;

	start = my_time();
	while (my_time() - start < ms_sec)
		usleep(500);
}

void	eat_slepp_think(t_philo *philo)
{
	sem_wait(FORK);
	printf_msg("has taken a fork", philo);
	sem_wait(FORK);
	printf_msg("has taken a fork", philo);
	philo->time_of_death = my_time() + philo->all->t_die;
	philo->state = EATING;
	philo->times_eat++;
	if (philo->times_eat == philo->all->parsed_times_eat)
		philo->all->done_eat++;
	printf_msg("is eating", philo);
	ft_usleep(philo->all->t_eat);
	sem_post(FORK);
	sem_post(FORK);
	philo->state = SLEEPING;
	printf_msg("is sleeping", philo);
	ft_usleep(philo->all->t_sleep);
	philo->state = THINKING;
	printf_msg("is thinking", philo);
}

void	start_life(t_philo *philo)
{
	/*pthread_t th;*/

	philo->time_of_death = my_time() + philo->all->t_die;
	/*pthread_create(&th, 0, check_life, philo);*/
	/*pthread_detach(th);*/
	while (!philo->all->end)
		eat_slepp_think(philo);
	return ;
}
