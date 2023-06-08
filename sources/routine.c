/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:08:43 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/08 12:29:39 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Wait until both forks are available.
// Die if time_to_die miliseconds has elapsed.
int	thinking(t_ph *ph, bool *first_time)
{
	t_data		*data;

	data = ph->data;
	if (data->a_ph_died == true)
		return (1);
	if (*first_time)
	{
		*first_time = false;
		ph->time_end_eating = get_timestamp(data);
	}
	else
		printf("%ld %d is thinking\n", get_timestamp(data), ph->id);
	while (data->fork[ph->id] != 1
		&& data->fork[(ph->id + 1) % data->philo_nb] != 1)
	{
		if (get_timestamp(data) >= ph->time_end_eating + data->time_to_die)
		{
			data->a_ph_died = true;
			printf("%ld %d died\n", get_timestamp(data), ph->id);
			return (1);
		}
	}
	return (0);
}

// Lock the fork array and the mutexes of the actual ph and its neighbor.
// Eat time_to_eat miliseconds and unlock the fork array and the mutexes.
int	eating(t_ph *ph)
{
	t_data	*data;

	data = ph->data;
	if (data->a_ph_died == true)
		return (1);
	data->fork[ph->id] = 0;
	data->fork[(ph->id + 1) % data->philo_nb] = 0;
	pthread_mutex_lock(&ph->mutex);
	printf("%ld %d has taken a fork\n", get_timestamp(data), ph->id);
	pthread_mutex_lock(&data->ph[(ph->id + 1) % data->philo_nb].mutex);
	printf("%ld %d has taken a fork\n", get_timestamp(data), ph->id);
	printf("%ld %d is eating\n", get_timestamp(data), ph->id);
	usleep(data->time_to_eat * 1000);
	ph->time_end_eating = get_timestamp(data);
	pthread_mutex_unlock(&ph->mutex);
	data->fork[ph->id] = 1;
	pthread_mutex_unlock(&data->ph[(ph->id + 1) % data->philo_nb].mutex);
	data->fork[(ph->id + 1) % data->philo_nb] = 1;
	return (0);
}

// Sleep time_to_sleep miliseconds.
int	sleeping(t_ph *ph)
{
	long int	time_to_wakeup;
	long int	timestamp;
	t_data		*data;

	data = ph->data;
	if (data->a_ph_died == true)
		return (1);
	time_to_wakeup = get_timestamp(data) + ph->data->time_to_sleep;
	printf("%ld %d is sleeping\n", get_timestamp(data), ph->id);
	timestamp = get_timestamp(data);
	while (timestamp < time_to_wakeup)
	{
		if (timestamp >= ph->time_end_eating + data->time_to_die)
		{
			data->a_ph_died = true;
			printf("%ld %d died\n", timestamp, ph->id);
			return (1);
		}
		timestamp = get_timestamp(data);
	}
	// usleep(ph->data->time_to_sleep * 1000);
	return (0);
}

// Function executed by the threads
void	*routine(void *arg)
{
	t_ph		*ph;
	int			meal;
	bool		first_time;

	ph = (t_ph *)arg;
	meal = 0;
	first_time = true;
	while (ph->data->meals_nb == -1 || meal < ph->data->meals_nb)
	{
		if (thinking(ph, &first_time))
			return ((void *)0);
		if (eating(ph))
			return ((void *)0);
		if (sleeping(ph))
			return ((void *)0);
		meal++;
	}
	return ((void *)0);
}
