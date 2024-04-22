
#include "philo.h"

void	ft_error(t_data *data, char *str)
{
	if (data)
		free(data);
	printf("%s", str);
	exit (0);
}

void	ft_freephilo(t_data *data, t_philo *philo)
{
	t_philo	*temp;
	int		i;

	i = 0;
	while (i < data->pcount)
	{
		pthread_mutex_destroy(&philo->fork);
		temp = philo->next;
		free(philo);
		philo = temp;
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_data		*data;
	
	if (argc < 5 || argc > 6)
		ft_error(NULL, "Error : usage = number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat\n");
	data = ft_setup(argc, argv);
	ft_thread_init(data);
	ft_freephilo(data, data->philo);
	pthread_mutex_destroy(&data->print);
	free(data);
	return (0);

}

