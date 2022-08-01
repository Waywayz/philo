#include "philo.h"

void	one_philo(t_value *value, t_philo *philo, int i)
{
	philo[i].index = i;
	philo[i].left = i;
	philo[i].right = (i + 1) % value->philo_numbers;
	philo[i].is_dead = NO;
	philo[i].data = value;
	philo[i].eat = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo[i].eat, NULL);
	if (value->eat_counter == -1)
		philo[i].eat_counter = -1;
	else
		philo[i].eat_counter = value->eat_counter;
}

t_philo	*philo_init(t_value *value)
{
	t_philo	*philo;
	int	i;

	i = -1;
	philo = malloc(sizeof(t_philo) * value->philo_numbers);
	value->stop = malloc(sizeof(pthread_mutex_t));
	value->msg = malloc(sizeof(pthread_mutex_t));
	value->death = malloc(sizeof(pthread_mutex_t));
	while (++i < value->philo_numbers)
		one_philo(value, philo, i);
	return (philo);
}

void	init_mutex(t_value *value)
{
	int	i;

	i = 0;
	pthread_mutex_init(value->msg, NULL);
	pthread_mutex_init(value->stop, NULL);
	pthread_mutex_init(value->death, NULL);
	while (i < value->philo_numbers)
	{
		pthread_mutex_init(value->forks + i, NULL);
		i++;
	}
}
