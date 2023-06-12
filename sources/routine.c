/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:08:43 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/12 16:28:48 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Thinking state
int	thinking(t_ph *ph)
{
	t_data		*data;

	data = ph->data;
	if (data->stop_simulation == true)
		return (-1);
	ph->state = THINKING;
	printf("%ld %d is thinking\n", get_time(data), ph->id);
	return (0);
}

// Lock the mutexes of the actual ph and its neighbor.
// Eat time_to_eat miliseconds and unlock the mutexes.
int	eating(t_ph *ph)
{
	t_data	*data;

	data = ph->data;
	if (data->stop_simulation == true)
		return (-1);
	pthread_mutex_lock(&ph->mutex);
	printf("%ld %d has taken a fork\n", get_time(data), ph->id);
	pthread_mutex_lock(&data->ph[(ph->id + 1) % data->philo_nb].mutex);
	printf("%ld %d has taken a fork\n", get_time(data), ph->id);
	ph->state = EATING;
	printf("%ld %d is eating\n", get_time(data), ph->id);
	usleep(data->time_to_eat * 1000);
	ph->last_meal = get_time(data);
	pthread_mutex_unlock(&ph->mutex);
	pthread_mutex_unlock(&data->ph[(ph->id + 1) % data->philo_nb].mutex);
	return (0);
}

// Sleep time_to_sleep miliseconds.
int	sleeping(t_ph *ph)
{
	t_data		*data;

	data = ph->data;
	if (data->stop_simulation == true)
		return (-1);
	ph->state = SLEEPING;
	printf("%ld %d is sleeping\n", get_time(data), ph->id);
	usleep(data->time_to_sleep * 1000);
	return (0);
}

// Function executed by the threads
void	*routine(void *arg)
{
	t_ph		*ph;

	ph = (t_ph *)arg;
	ph->last_meal = get_time(ph->data);
	while (ph->data->meals_nb == -1 || ph->meal < ph->data->meals_nb)
	{
		if (eating(ph) == -1)
			break ;
		if (sleeping(ph) == -1)
			break ;
		if (thinking(ph) == -1)
			break ;
		ph->meal++;
	}
	return ((void *)0);
}
