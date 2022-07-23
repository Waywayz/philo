#include "philo.h"

void	init_mutex(t_value *value)
{
	int	i;

	i = 1;
	while (i < value->philo_numbers)
	{
		pthread_mutex_init(value->forks + i, NULL);
		i++;
	}
	pthread_mutex_init(value->death, NULL);
	pthread_mutex_init(value->stop, NULL);
	pthread_mutex_init(value->msg, NULL);
}

void	philo_day(t_value *value)
{
	init_mutex(value);
}

int	main(int ac, char **av)
{
	t_value	value;

	if (ac != 5 && ac != 6)
		printf("Error numbers of argument\n");
	else
	{
		if (init_arg(av, &value))
			return (0);
		value.start = get_time();
		philo_day(&value);
	}
	return (0);
}
