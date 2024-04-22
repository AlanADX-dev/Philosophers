#include "philo.h"

void	ft_usleep(int time)
{
	long int	cur;

	cur = timestamp();
	while (timestamp() - cur < time)
		usleep(250);
}

long int    timestamp(void)
{
    	struct timeval    tv;

    	gettimeofday(&tv, NULL);
    	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

int		ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-' && str[i] != '+' && (str[i] < '0' || str[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

void	ft_checkatoi(char *str, long res, t_data *data)
{
	if (ft_strisdigit(str) == 1)
		ft_error(data, "ERROR : Use only digit character.\n");
	if (res > 2147483647 || res < -2147483648)
		ft_error(data, "ERROR : Values between INT MIN and INT MAX.\n");
}

int		ft_atoi(t_data *data, char *str)
{
	long	res;
	int		sign;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	res *= sign;
	ft_checkatoi(str, res, data);
	return ((int)res);
}