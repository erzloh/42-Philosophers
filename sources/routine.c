/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:08:43 by eholzer           #+#    #+#             */
/*   Updated: 2023/03/13 11:05:55 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Wait until both forks are available.
// Die if time_to_die miliseconds has elapsed.
int	thinking(t_ph *ph)
{
	long int	time_start_thinking;
	t_data		*data;

	data = ph->data;
	time_start_thinking = get_timestamp(data);
	printf("%ld %d is thinking\n", get_timestamp(data), ph->id);
	while (data->fork[ph->id] != 1
		&& data->fork[(ph->id + 1) % data->philo_nb] != 1)
	{
		if (get_timestamp(data) >= time_start_thinking + data->time_to_die)
		{
			printf("%ld %d died\n", get_timestamp(data), ph->id);
			return (1);
		}
	}
	return (0);
}

// Lock the fork array and the mutexes of the actual ph and its neighbor.
// Eat time_to_eat miliseconds and unlock the fork array and the mutexes.
void	eating(t_ph *ph)
{
	t_data	*data;

	data = ph->data;
	data->fork[ph->id] = 0;
	data->fork[(ph->id + 1) % data->philo_nb] = 0;
	pthread_mutex_lock(&ph->mutex);
	printf("%ld %d has taken a fork\n", get_timestamp(data), ph->id);
	pthread_mutex_lock(&data->ph[(ph->id + 1) % data->philo_nb].mutex);
	printf("%ld %d has taken a fork\n", get_timestamp(data), ph->id);
	printf("%ld %d is eating\n", get_timestamp(data), ph->id);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&ph->mutex);
	data->fork[ph->id] = 1;
	pthread_mutex_unlock(&data->ph[(ph->id + 1) % data->philo_nb].mutex);
	data->fork[(ph->id + 1) % data->philo_nb] = 1;
}

// Sleep time_to_sleep miliseconds.
void	sleeping(t_ph *ph)
{
	printf("%ld %d is sleeping\n", get_timestamp(ph->data), ph->id);
	usleep(ph->data->time_to_sleep * 1000);
}

// Function executed by the threads
void	*routine(void *arg)
{
	t_ph		*ph;
	int			meal;

	ph = (t_ph *)arg;
	meal = 0;
	while (ph->data->meals_nb == -1 || meal < ph->data->meals_nb)
	{
		if (thinking(ph))
			return ((void *)0);
		eating(ph);
		sleeping(ph);
		meal++;
	}
	return ((void *)0);
}
