#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include  <string.h>
# include  <stdio.h>
# include  <stdlib.h>
# include  <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define DIED 4

struct	s_all;

typedef struct s_philo
{
	unsigned long	time_of_death;
	struct s_all	*all;
	int				id;
	int				left_fork;
	int				right_fork;
	int				state;
	int				times_eat;
}	t_philo;

typedef struct s_all
{
	unsigned long	start;
	int				philosophers_number;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				parsed_times_eat;
	int				end;
	int				done_eat;
	int				*colors;
	t_philo			*philo;
	pthread_mutex_t	write;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	*forks;
}		t_all;

unsigned long	my_time(void);
void			error(t_all *all, int i);
void			free_all(t_all *all);
void			init_all(t_all *all);
void			get_others_args(t_all *all, char **av);
void			get_times_eat(t_all *all, int ac, char **av);
void			start(t_all *all);
void			ft_putnbr(unsigned long n);
void			*start_life(void *this_philo);
void			printf_msg(char *msg, t_philo *philo);
void			ft_usleep(unsigned long ms_sec);
int				ft_atoi(char *str);
int				get_args(t_all *all, int ac, char **av);

#endif
