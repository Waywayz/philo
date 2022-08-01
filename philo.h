#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define YES 1
# define NO 0
# define DIED 2
# define THINKING 3
# define EATING 4
# define FORK 1
# define SLEEPING 6
# define FINISH 6

typedef struct	s_value
{
	pthread_t	*threads;
	pthread_mutex_t	*death;
	pthread_mutex_t	*msg;
	pthread_mutex_t	*stop;
	pthread_mutex_t	*forks;
	unsigned int	start;
	int		philo_numbers;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		max_eat;
	int		current_eat;
	int		is_dead;
	int		eat_counter;
}		t_value;

typedef struct	s_philo
{
	pthread_mutex_t	*eat;
	t_value		*data;
	unsigned int	next_meal;
	unsigned int	eating_time;
	int		index;
	int		right;
	int		left;
	int		is_dead;
	int		eat_counter;
}		t_philo;

int		ft_strlen(char *str);
int		init_arg(char **av, t_value *value);
t_philo		*philo_init(t_value *value);
unsigned int	get_time(void);
void		init_mutex(t_value *value);
void		*philo_day(void *arg);
void		print_msg(int num, t_philo *philo);
void		ft_clean(t_value *value, t_philo *philo);
int		check_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);

#endif
