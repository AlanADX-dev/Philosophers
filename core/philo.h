#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
    pthread_mutex_t     fork;
    pthread_t           tid;
    int                 n;
    int                 sfork;
    int                 state;
    int                 cmeals;
    long int            lastmeal;
    struct s_philo      *next;
    struct s_data       *data;
}       t_philo;

typedef struct s_data
{
    pthread_mutex_t     print;
    pthread_mutex_t     pdead;
    int                 pcount;
    int                 tdie;
    int                 teat;
    int                 tsleep;
    int                 meals;
    int                 dead;
    long int            currentime;
    t_philo             *philo;
}       t_data;

void    *hasta_la_muerte(void *data);
void	ft_usleep(int time);
void	ft_error(t_data *data, char *str);
void	ft_thread_init(t_data *data);
long    timestamp(void);
t_data  *ft_setup(int argc, char **argv);
int     ft_atoi(t_data *data, char *str);
int		ft_checkdeath(t_data *data, t_philo *philo);

# define BLACK  "\e[1;30m"
# define RED  "\e[1;31m"
# define GREEN  "\e[1;32m"
# define YELLOW  "\e[1;33m"
# define BLUE  "\e[1;34m"
# define PURPLE  "\e[1;35m"
# define WHITE  "\e[1;37m"

#endif
