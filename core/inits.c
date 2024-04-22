#include "philo.h"

void	ft_thread_init(t_data *data)
{
    int i;
    t_philo		*philo;

	philo = data->philo;
    i = 0;
    while (i < data->pcount)
    {
        	pthread_create(&philo->tid, NULL, hasta_la_muerte, philo);
        	philo = philo->next;
        	i++;
    }
    i = 0;
    while (i < data->pcount)
    {
        	pthread_join(philo->tid, NULL);
        	philo = philo->next;
        	i++;
    }
}

void		*ft_init_philo(t_data *data, int n, t_philo *first)
{
    t_philo    *next;
    int        index;
	
    first = malloc(sizeof(t_philo));
    next = first;
    index = 1;
    while (index <= n)
    {
        next->n = index;
        next->sfork = 0;
        next->state = 0;
		if (next->n % 2 == 0)
			next->state = 4;
        next->data = data;
		next->cmeals = data->meals;
		next->lastmeal = data->currentime;
        pthread_mutex_init(&next->fork, NULL);
        if (index + 1 <= n)
        {
            next->next = malloc(sizeof(t_philo));
            next = next->next;
		}
        index++;
    }
    next->next = first;
}

void	ft_init_data(t_data *data, int argc, char **argv)
{
	data->pcount = ft_atoi(data, argv[1]);
	if (data->pcount <= 0)
		ft_error(data, "ERROR : invalid number of philosopher.\n");
	data->tdie = ft_atoi(data, argv[2]);
	if (data->tdie < 60)
		ft_error(data, "ERROR : invalid time to death.\n");
	data->teat = ft_atoi(data, argv[3]);
	if (data->teat < 60)
		ft_error(data, "ERROR : invalid time to eat.\n");
	data->tsleep = ft_atoi(data, argv[4]);
	if (data->tsleep < 60)
		ft_error(data, "ERROR : invalid time to sleep.\n");
	data->currentime = timestamp();
	if(argc == 6)
	{
		data->meals = ft_atoi(data, argv[5]);
		if (data->meals < 0)
			ft_error(data, "ERROR : invalid meal count.\n");
	}
	else
		data->meals = -1;
	data->dead = 0;
}

t_data	*ft_setup(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_init_data(data, argc, argv);
	data->currentime = timestamp();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->pdead, NULL);
	data->philo = ft_init_philo(data, data->pcount, data->philo);
	return (data);
}
