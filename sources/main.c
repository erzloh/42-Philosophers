/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:18:22 by eholzer           #+#    #+#             */
/*   Updated: 2023/03/02 16:16:13 by eholzer          ###   ########.fr       */
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

	ph_ptr = (t_ph *)arg;
	printf("thread %d has started\n", ph_ptr->id);
	pthread_mutex_lock(&ph_ptr->data_ptr->mutex);
	printf("%ld thread %d has taken a fork\n", get_timestamp(ph_ptr->data_ptr), ph_ptr->id);
	usleep(1000000);
	pthread_mutex_unlock(&ph_ptr->data_ptr->mutex);
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
		i++;
	}
	return (0);
}

void	free_memory(t_data *data_ptr)
{
	pthread_mutex_destroy(&data_ptr->mutex);
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
