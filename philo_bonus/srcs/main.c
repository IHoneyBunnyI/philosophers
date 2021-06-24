#include "philo_bonus.h"

void	init_all(t_all *all)
{
	int i;
	int color;

	i = -1;
	color = 37;
	all->philosophers_number = 0;
	all->t_die = 0;
	all->t_eat = 0;
	all->t_sleep = 0;
	all->parsed_times_eat = -1;
	all->start = 0;
	all->philo = 0;
	all->end = 0;
	all->done_eat = 0;
	all->colors = malloc(sizeof(int) * 8);
	if (!all->colors)
	{
		all->colors = 0;
		error(all, 2);
	}
	while (++i < 8)
		all->colors[i] = color--;
}

void	init_philos_forks(t_all *all)
{
	int i;

	i = -1;
	all->philo = malloc(sizeof(t_philo) * all->philosophers_number);
	if (!all->philo)
		error(all, 2);
	while (++i < all->philosophers_number)
	{
		all->philo[i].all = all;
		all->philo[i].state = THINKING;
		all->philo[i].id = i + 1;
		all->philo[i].times_eat = 0;
		all->philo[i].pid = 0;
	}
	sem_unlink("forks");
	sem_unlink("write");
	all->forks = sem_open("forks", O_CREAT | O_EXCL, 644, all->philosophers_number);
	all->write = sem_open("write", O_CREAT | O_EXCL, 644, 1);
}

void	start_simulation(t_all *all)
{
	int i;
	pid_t pid;

	i = -1;
	while (i < all->philosophers_number)
	{
		pid = fork();
		if (pid == 0)
			start_life(&all->philo[i]);
		if (pid > 0)
			all->philo[i].pid = pid;
		else
			return ;
		i++;
	}
}

void	check_state(t_all *all)
{
	int status;
	while (LIFE)
	{
		waitpid(-1, &status, 0);
		status = status >> 8;
		if (status == DIED)
			return ;
		else if (status == FULL)
			all->done_eat++;
		if (all->done_eat == all->philosophers_number)
		{
			sem_wait(all->write);
			return ;
		}
	}
}

int		main(int ac, char **av)
{
	t_all	all;
	int	i;

	init_all(&all);
	if (ac < 5 || ac > 6)
		error(&all, 1);
	if (!get_args(&all, ac, av + 1))
		error(&all, 1);
	init_philos_forks(&all);
	all.start = my_time();
	start_simulation(&all);
	check_state(&all);
	i = -1;
	while (++i < all.philosophers_number)
		kill(all.philo[i].pid, 9);
	free_all(&all);
	return 0;
}
