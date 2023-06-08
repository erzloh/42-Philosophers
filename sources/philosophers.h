/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:59:59 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/08 12:23:30 by eholzer          ###   ########.fr       */
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
	long int		time_end_eating;
}	t_ph;

typedef struct s_data
{
	t_ph			*ph;
	int				*fork;
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_nb;
	bool			a_ph_died;
	int				*res;
	struct timeval	curr_time;
	long int		init_sec;
	long int		init_usec;
}	t_data;

// Utils functions
int			ft_atoi(const char *str);
void		free_memory(t_data *data);
long int	get_timestamp(t_data *data);
int			error_exit(t_data *data, int error_code);

// Init functions
int			check_arguments(int ac);
int			init_philo(t_data *data);
int			init_data(int ac, char **av, t_data *data);

// Threads functions
int			create_threads(t_data *data);
int			join_threads(t_data *data);
void		*routine(void *arg);

#endif