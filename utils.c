#include "philo.h"

int	check_eat(t_philo *philo)
{
	if ((philo->data->eat_counter != -1) && philo->data->current_eat >= philo->data->max_eat)
	{
		philo->data->is_dead = YES;
		pthread_mutex_lock(philo->eat);
		print_msg(FINISH, philo);
		pthread_mutex_unlock(philo->data->stop);
		return (0);
	}
	return (1);
}

void	ft_clean(t_value *value, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(value->death);
	pthread_mutex_destroy(value->msg);
	pthread_mutex_destroy(value->stop);
	while (i < value->philo_numbers)
	{
		pthread_mutex_destroy(value->forks + i);
		pthread_mutex_destroy(philo[i].eat);
		free(philo[i].eat);
		i++;
	
	}
	free(philo);
	free(value->forks);
	free(value->threads);
	free(value->death);
	free(value->msg);
	free(value->stop);
}

void	print_msg(int num, t_philo *philo)
{
	unsigned int	time;

	pthread_mutex_lock(philo->data->msg);
	time = get_time() - philo->data->start;
	if (num == FORK)
		printf("%u\t%d has taken a fork\n", time, philo->index + 1);
	else if (num == EATING)
		printf("%u\t%d is eating\n", time, philo->index + 1);
	else if (num == SLEEPING)
		printf("%u\t%d is sleeping\n", time, philo->index + 1);
	else if (num == THINKING)
		printf("%u\t%d is thinking\n", time, philo->index + 1);
	else if (num == DIED)
		printf("%u\t%d died\n", time, philo->index + 1);
	else if (num == FINISH)
		printf("Program is finish\n");
	if (num != DIED && num != FINISH)
		pthread_mutex_unlock(philo->data->msg);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
