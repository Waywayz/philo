#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	usleep(10);
	print_msg(SLEEPING, philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->eat);
	print_msg(EATING, philo);
	if (philo->data->eat_counter != -1)
		philo->data->current_eat++;
	philo->eating_time = get_time();
	philo->next_meal = philo->eating_time + (unsigned int)philo->data->time_to_die;
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left]);
	pthread_mutex_unlock(&philo->data->forks[philo->right]);
	pthread_mutex_unlock(philo->eat);
}

void	next_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left]);
	print_msg(FORK, philo);
	pthread_mutex_lock(&philo->data->forks[philo->right]);
	print_msg(FORK, philo);
}

void	*philo_alive(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->next_meal < get_time())
		{
			philo->data->is_dead = YES;
			pthread_mutex_lock(philo->eat);
			print_msg(DIED, philo);
			pthread_mutex_unlock(philo->data->stop);
			break ;
		}
	}
	return (NULL);
}

void	*philo_day(void *arg)
{
	t_philo		*philo;
	pthread_t	death;

	philo = arg;
	philo->next_meal = get_time() + (unsigned int)philo->data->time_to_die;
	pthread_create(&death, NULL, philo_alive, philo);
	pthread_detach(death);
	while (1)
	{
		if (philo->data->is_dead)
			break ;
		next_fork(philo);
		philo_eat(philo);
		if (!check_eat(philo))
			break ;
		philo_sleep(philo);
		print_msg(THINKING, philo);
	}
	return (NULL);
}
