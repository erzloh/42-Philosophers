/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:18:22 by eholzer           #+#    #+#             */
/*   Updated: 2023/03/06 15:19:48 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_timestamp(t_data *data_ptr)
{
	long int	timestamp;

	gettimeofday(&data_ptr->curr_time, NULL);
	timestamp = (data_ptr->curr_time.tv_usec - data_ptr->init_time) / 1000;
	return (timestamp);
}

// Function executed by the thread
void	*routine(void *arg)
{
	t_ph		*ph_ptr;
	int			id;
	t_data		*data_ptr;

	ph_ptr = (t_ph *)arg;
	id = ph_ptr->id;
	data_ptr = ph_ptr->data_ptr;
	printf("thread %d has started\n", id);
	if (data_ptr->fork[id] == 1
		&& data_ptr->fork[(id + 1) % data_ptr->philo_nb] == 1)
	{
		data_ptr->fork[id] = 0;
		data_ptr->fork[(id + 1) % data_ptr->philo_nb] = 0;
		pthread_mutex_lock(&ph_ptr->mutex);
		printf("%ld thread %d has taken its fork\n",
			get_timestamp(ph_ptr->data_ptr), id);
		// usleep(1000000);
		pthread_mutex_lock(&data_ptr->ph[(id + 1) % data_ptr->philo_nb].mutex);
		printf("%ld thread %d has taken its neighbor's fork\n",
			get_timestamp(ph_ptr->data_ptr), id);
		pthread_mutex_unlock(&ph_ptr->mutex);
		data_ptr->fork[id] = 1;
		pthread_mutex_unlock(&data_ptr->ph[(id + 1) % data_ptr->philo_nb].mutex);
		data_ptr->fork[(id + 1) % data_ptr->philo_nb] = 1;
	}
	return ((void *)0);
}

// Create the threads represented as philosophers
// Return 0 if it succeeded
int	create_threads(t_data *data_ptr)
{
	int	i;

	i = 0;
	while (i < data_ptr->philo_nb)
	{
		if (pthread_create(&data_ptr->ph[i].th, NULL,
				&routine, &data_ptr->ph[i]) != 0)
		{
			printf("Error: Couldn't create the thread.");
			return (-1);
		}
		printf("thread %d is created\n", i);
		i++;
	}
	return (0);
}

// Join the threads represented as philosophers
// Return 0 if it succeeded
int	join_threads(t_data *data_ptr)
{
	int	i;

	i = 0;
	while (i < data_ptr->philo_nb)
	{
		if (pthread_join(data_ptr->ph[i].th, NULL) != 0)
		{
			printf("Error: Couldn't join the thread.");
			return (-1);
		}
		printf("thread %d has finished\n", i);
		pthread_mutex_destroy(&data_ptr->ph[i].mutex);
		i++;
	}
	return (0);
}

void	free_memory(t_data *data_ptr)
{
	free(data_ptr->fork);
	free(data_ptr->ph);
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
