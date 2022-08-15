#include "philo.h"

static void	*philo_eat_two(t_philos *philo, struct timeval end)
{
	if (*philo->alive == 0)
	{
		pthread_mutex_unlock(philo->m_alive);
		pthread_mutex_lock(philo->m_alive);
		if (*philo->alive == 0)
		{
			pthread_mutex_unlock(philo->m_alive);
			pthread_mutex_lock(philo->write);
			pthread_mutex_lock(philo->m_alive);
			if (*philo->alive == 0)
				printf("%ld %d \033[4;33mis eating\033[0m\n",
					get_time(end, philo->start, philo), philo->number);
			pthread_mutex_unlock(philo->m_alive);
			pthread_mutex_unlock(philo->write);
		}
		else
			pthread_mutex_unlock(philo->m_alive);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (pthread_mutex_unlock(philo->m_alive), NULL);
	}
	return (philo);
}

void	*philo_eat(t_philos *philo)
{
	struct timeval	end;

	pthread_mutex_lock(philo->m_alive);
	if (*philo->alive == 1)
	{
		pthread_mutex_unlock(philo->m_alive);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (NULL);
	}
	pthread_mutex_unlock(philo->m_alive);
	pthread_mutex_lock(philo->m_alive);
	if ((philo_eat_two(philo, end) == NULL))
		return (NULL);
	pthread_mutex_lock(philo->m_last);
	philo->last_eat = get_time(end, philo->start, philo);
	pthread_mutex_unlock(philo->m_last);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (philo);
}
