#include "philo.h"

void	philo_thread(t_value *value, t_philo **philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(value->stop);
	while (i < value->philo_numbers)
	{
		pthread_create(value->threads + i, NULL, philo_day, philo + i);
		pthread_detach(value->threads[i]);
		i++;
		usleep(100);
	}
	pthread_mutex_lock(value->stop);
	printf("TEST\n");
}

int	main(int ac, char **av)
{
	t_value	value;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		printf("Error numbers of argument\n");
	else
	{
		if (init_arg(av, &value))
			return (0);
		philo = philo_init(&value);
		value.start = get_time();
		init_mutex(&value);
		philo_thread(&value, &philo);
		ft_clean(&value, philo);
	}
	return (0);
}
