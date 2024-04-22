#include "philo.h"

int	ft_sleep(t_data	*data, t_philo *philo)
{
	long	temp;

	if (philo->state == 4)
	{
		temp = timestamp();
		pthread_mutex_lock(&data->print);
		printf("%s[%ld ms] %d is sleeping.\n", BLUE, temp - data->currentime, philo->n);
		pthread_mutex_unlock(&data->print);
		if (data->tsleep + data->teat >= data->tdie)
		{
			ft_usleep(data->tdie);
			ft_checkdeath(data, philo);
			return (1);
		}
		ft_usleep(data->tsleep);
		philo->state = 0;
	}
	return (0);
}

void	ft_eat(t_data *data, t_philo *philo)
{
	long	temp;

	if (philo->state == 3)
	{
		temp = timestamp();
		pthread_mutex_lock(&data->print);
		printf("%s[%ld ms] %d is eating.\n", GREEN, temp - data->currentime, philo->n);
		pthread_mutex_unlock(&data->print);
		philo->lastmeal = temp;
		ft_usleep(data->teat);
		pthread_mutex_lock(&philo->fork);
		philo->sfork = 0;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
		philo->next->sfork = 0;
		pthread_mutex_unlock(&philo->next->fork);
		philo->cmeals--;
		philo->state++;
	}
}

void	ft_takefork(t_philo *philo, pthread_mutex_t *fork, int *used)
{
	long	temp;

	if (philo->state == 1 || philo->state == 2)
	{
		pthread_mutex_lock(fork);
		if (*used == 0)
		{
			*used = 1;
			pthread_mutex_unlock(fork);
			philo->state++;
			temp = timestamp();
			pthread_mutex_lock(&philo->data->print);
			printf("%s[%ld ms] %d has taken a fork.\n", PURPLE, temp - philo->data->currentime, philo->n);
			pthread_mutex_unlock(&philo->data->print);
		}
		else
		{
			pthread_mutex_unlock(fork);
			usleep(250);
		}
	}
}

void	ft_think(t_data	*data, t_philo *philo)
{
	long	temp;

	if (philo->state == 0)
	{
		philo->state++;
		temp = timestamp();
		pthread_mutex_lock(&data->print);
		printf("%s[%ld ms] %d is thinking.\n", YELLOW, temp - data->currentime, philo->n);
		pthread_mutex_unlock(&data->print);
	}
}


void	*hasta_la_muerte(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	while(philo->cmeals !=0)
	{
		if (ft_checkdeath(philo->data, philo) == 1)
			return (NULL);
		ft_think(philo->data, philo);
		if (ft_checkdeath(philo->data, philo) == 1)
			return (NULL);
		ft_takefork(philo, &philo->fork, &philo->sfork);
		if (ft_checkdeath(philo->data, philo) == 1)
			return (NULL);
		ft_takefork(philo, &philo->next->fork, &philo->next->sfork);
		if (ft_checkdeath(philo->data, philo) == 1)
			return (NULL);
		ft_eat(philo->data, philo);
		if (ft_checkdeath(philo->data, philo) == 1)
			return (NULL);
		if (ft_sleep(philo->data, philo) == 1)
			return (NULL);
		if (philo->cmeals == -2147483648)
			philo->cmeals = -1;
	}
	return (NULL);
}