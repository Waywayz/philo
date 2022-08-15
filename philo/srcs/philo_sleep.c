#include "philo.h"

static void	philo_sleep2(t_philos *philo, struct timeval end)
{
	pthread_mutex_unlock(philo->m_alive);
	pthread_mutex_lock(philo->m_alive);
	if (*philo->alive == 0)
	{
		pthread_mutex_unlock(philo->m_alive);
		pthread_mutex_lock(philo->write);
		pthread_mutex_lock(philo->m_alive);
		if (*philo->alive == 0)
			printf("%ld %d \033[1;32mis sleeping\033[0m\n",
				get_time(end, philo->start, philo), philo->number);
		if (*philo->alive == 0)
			printf("%ld %d \033[3;32mis thinking\033[0m\n",
				get_time(end, philo->start, philo), philo->number);
		pthread_mutex_unlock(philo->m_alive);
		pthread_mutex_unlock(philo->write);
	}
	else
		pthread_mutex_unlock(philo->m_alive);
}

void	*philo_sleep(t_philos *philo)
{
	struct timeval	end;

	pthread_mutex_lock(philo->m_alive);
	if (*philo->alive == 1)
	{
		pthread_mutex_unlock(philo->m_alive);
		return (NULL);
	}
	pthread_mutex_unlock(philo->m_alive);
	pthread_mutex_lock(philo->m_alive);
	if (*philo->alive == 0)
		philo_sleep2(philo, end);
	else
		pthread_mutex_unlock(philo->m_alive);
	usleep(philo->time_to_sleep * 1000);
	return (philo);
}
