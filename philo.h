#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

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
	int		is_dead;
}		t_value;

int		ft_strlen(char *str);
int		init_arg(char **av, t_value *value);
unsigned int	get_time(void);

# endif
