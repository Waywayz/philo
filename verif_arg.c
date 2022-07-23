#include "philo.h"

int	error_arg(t_value *value, char *msg, int ret)
{
	if (value)
	{
		if (value->threads)
			free(value->threads);
		if (value->forks)
			free(value->forks);
	}
	printf("%s\n", msg);
	return (ret);
}

int	init_value_2(t_value *value, int num, int i)
{
	if (i == 3)
	{
		if (num < 60)
			return (error_arg(value, "Error: time_to_eat can't be less than 60ms", 1));
		value->time_to_eat = num;
	}
	else if (i == 4)
	{
		if (num < 60)
			return (error_arg(value, "Error: time_to_sleep can't be less than 60ms", 1));
		value->time_to_sleep = num;
	}
	else
		value->max_eat = num;
	return (0);
}

int	init_value(t_value *value, int num, int i)
{
	if (i == 1)
	{
		if (num == 0)
			return (error_arg(value, "Error: no philosopher", 1));
		value->philo_numbers = num;
		value->threads = malloc(sizeof(pthread_t) * num);
		value->forks = malloc(sizeof(pthread_mutex_t) * num);
	}
	else if (i == 2)
	{
		if (num < 60)
			return (error_arg(value, "Error: time_to_die can't be less than 60ms", 1));
		value->time_to_die = num;
	}
	else
		init_value_2(value, num, i);
	return (0);
}

int	verif_arg(char *str, t_value *value)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (ft_strlen(str) < 1)
		return (error_arg(value, "Error: empty argument", 1));
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = num * 10 + (str[i] - '0');
		else
			return (error_arg(value, "Error: bad argument", 1));
		i++;
	}
	return (num);
}

int	init_arg(char **av, t_value *value)
{
	int	i;
	int	num;

	i = 1;
	while (av[i])
	{
		num = verif_arg(av[i], value);
		if (init_value(value, num, i))
			return (1);
		i++;
	}
	return (0);
}
