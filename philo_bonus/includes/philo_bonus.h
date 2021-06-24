#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include  <string.h>
# include  <stdio.h>
# include  <stdlib.h>
# include  <signal.h>
# include  <unistd.h>
# include  <unistd.h>
# include  <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# define THINKING 1
# define LIFE 1
# define EATING 2
# define SLEEPING 3
# define DIED 5
# define FORK philo->all->forks
# define WRITE philo->all->write

struct s_all;

typedef struct	s_philo
{
	struct s_all *all;
	int id;
	int state;
	int times_eat;
	unsigned long time_of_death;
	pid_t	pid;
}	t_philo;

typedef struct	s_all
{
	int	philosophers_number;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	parsed_times_eat;
	unsigned long start;
	sem_t	*forks;
	sem_t	*write;
	sem_t	*end_mutex;
	t_philo *philo;
	int	end;
	int	done_eat;
}				t_all;


void	error(t_all *all, int i);
int	get_args(t_all *all, int ac, char **av);
int	ft_atoi(char *str);
void	free_all(t_all *all);
unsigned long	my_time();
void	start_life(t_philo *philo);
void	ft_usleep(unsigned long ms_sec);
void	printf_msg(char *msg, t_philo *philo);

#endif
