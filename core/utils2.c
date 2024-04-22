#include "philo.h"

int	ft_checkdeath(t_data *data, t_philo *philo)
{
	long temp;

	pthread_mutex_lock(&data->pdead);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->pdead);
		return (1);
	}
	temp = timestamp();
	if (temp - philo->lastmeal >= data->tdie)
	{
		data->dead = 1;
		pthread_mutex_unlock(&data->pdead);
		pthread_mutex_lock(&data->print);
		printf("%s[%ld ms] %d died.\n", RED, temp - data->currentime, philo->n);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->pdead);
	return (0);
}

