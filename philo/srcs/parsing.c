#include "philo.h"

int	check_validity(char **argv, int i, int j, int argc)
{
	while (++i < argc)
	{
		while (argv[i][j] != '\0')
		{
			if (j == 0 && argv[i][j] == '\0')
			{
				printf("Empty argument\n");
				return (1);
			}
			if ((argv[i][j] > 57 || argv[i][j] < 48) || (argv[i][0] == '0'
				&& argv[i][1] == '\0'))
			{
				printf("Bad argument\n");
				return (1);
			}
			j++;
		}
		if (j == 0)
		{
			printf("Empty argument\n");
			return (1);
		}
		j = 0;
	}
	return (0);
}

int	check_args(char **argv, int argc, int i)
{
	if (argc > 6)
		argc = 6;
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) > 2147483647)
			return ((printf("Integer overflow\n"), 1));
		if (ft_atoi(argv[i]) < 0)
			return (printf("Invalid format\n"), 1);
	}
	return (0);
}
