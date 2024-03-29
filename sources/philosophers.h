/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:59:59 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/19 15:52:49 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H 
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define ERROR 1

// Philosopher's states enums
typedef enum e_state
{
	START,
	EATING,
	SLEEPING,
	THINKING
}	t_state;

// Struct prototypes
struct					s_data;
typedef struct s_data	t_data;

// Initialize structs
typedef struct s_ph
{
	pthread_t		th;
	int				id;
	t_data			*data;
	pthread_mutex_t	mutex;
	long int		last_meal;
	int				meal;
	t_state			state;
}	t_ph;

typedef struct s_data
{
	t_ph			*ph;
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_nb;
	bool			stop_simulation;
	int				*res;
	struct timeval	curr_time;
	long int		init_sec;
	long int		init_usec;
}	t_data;

// Arguments checking functions
int			check_alpha(char **av);
int			check_int_max(char **av);
double		check_int_max_atoi(const char *str);
int			check_arguments(int ac, char **av);

// Utils functions
int			ft_atoi(const char *str);
void		free_memory(t_data *data);
long int	get_time(t_data *data);
int			error_exit(t_data *data, int error_code);
void		ft_sleep(int msec, t_data *data);

// Init functions
int			init_philo(t_data *data);
int			init_data(int ac, char **av, t_data *data);

// Threads functions
int			create_threads(t_data *data);
int			join_threads(t_data *data);
void		*routine(void *arg);
int			unlock_mutexes(t_data *data, t_ph *ph);

// Main thread
int			check_philos(t_data *data);

#endif