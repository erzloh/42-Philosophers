/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:59:59 by eholzer           #+#    #+#             */
/*   Updated: 2023/02/23 15:53:52 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H 
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

// Initialize structs
typedef struct s_data
{
	pthread_t		*ph;
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_nb;
	pthread_mutex_t	mutex;
	int				*res;
}	t_data;

// Utils functions
int		ft_atoi(const char *str);

// Init functions
int		check_arguments(int ac);
void	init_data(int ac, char **av, t_data *data);

#endif