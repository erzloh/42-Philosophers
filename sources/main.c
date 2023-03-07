/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:18:22 by eholzer           #+#    #+#             */
/*   Updated: 2023/03/07 17:27:22 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	absolute(long int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

long int	get_timestamp(t_data *data)
{
	long int	sec;
	long int	msec;
	long int	timestamp;

	gettimeofday(&data->curr_time, NULL);
	sec = data->curr_time.tv_sec - data->init_sec;
	gettimeofday(&data->curr_time, NULL);
	if (data->curr_time.tv_usec > data->init_usec)
		msec = data->curr_time.tv_usec - data->init_usec;
	else
		msec = (1000000 - data->init_usec) + data->curr_time.tv_usec;
	timestamp = (sec * 1000) + (msec / 1000);
	return (timestamp);
}

// Function executed by the thread
void	*routine(void *arg)
{
	t_ph		*ph;
	int			id;
	t_data		*data;

	ph = (t_ph *)arg;
	id = ph->id;
	data = ph->data;
	// printf("thread %d has started\n", id);
	while (data->fork[id] != 1
		&& data->fork[(id + 1) % data->philo_nb] != 1)
	{
	}
	data->fork[id] = 0;
	data->fork[(id + 1) % data->philo_nb] = 0;
	pthread_mutex_lock(&ph->mutex);
	printf("%ld %d has taken a fork\n",
		get_timestamp(data), id);
	pthread_mutex_lock(&data->ph[(id + 1) % data->philo_nb].mutex);
	printf("%ld %d has taken a fork\n",
		get_timestamp(data), id);
	printf("%ld %d is eating\n", get_timestamp(data), id);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&ph->mutex);
	data->fork[id] = 1;
	pthread_mutex_unlock(&data->ph[(id + 1) % data->philo_nb].mutex);
	data->fork[(id + 1) % data->philo_nb] = 1;
	return ((void *)0);
}

// Create the threads represented as philosophers
// Return 0 if it succeeded
int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->ph[i].th, NULL,
				&routine, &data->ph[i]) != 0)
		{
			printf("Error: Couldn't create the thread.");
			return (-1);
		}
		// printf("thread %d is created\n", i);
		i++;
	}
	return (0);
}

// Join the threads represented as philosophers
// Return 0 if it succeeded
int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(data->ph[i].th, NULL) != 0)
		{
			printf("Error: Couldn't join the thread.");
			return (-1);
		}
		// printf("thread %d has finished\n", i);
		pthread_mutex_destroy(&data->ph[i].mutex);
		i++;
	}
	return (0);
}

void	free_memory(t_data *data)
{
	free(data->fork);
	free(data->ph);
}

int	main(int ac, char **av)
{
	t_data			data;

	if (check_arguments(ac))
		return (1);
	if (init_data(ac, av, &data))
		return (1);
	if (create_threads(&data))
		return (1);
	if (join_threads(&data))
		return (1);
	free_memory(&data);
	return (0);
}
