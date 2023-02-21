/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:18:22 by eholzer           #+#    #+#             */
/*   Updated: 2023/02/21 16:02:15 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function executed by the thread
void	*routine()
{
	// pthread_mutex_lock(&data->mutex);
	printf("thread is being used\n");
	// pthread_mutex_unlock(&data->mutex);
	return (0);
}

// Create the threads represented as philosophers
// Return 0 if it succeeded
int	create_philosophers(t_data *data)
{
	int	i;

	data->ph = malloc(sizeof(pthread_t) * data->philo_nb);
	if (!data->ph)
	{
		printf("Error: malloc() couldn't allocate memory.");
		return (-1);
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->ph[i], NULL, &routine, data) != 0)
		{
			printf("Error: Couldn't create the thread.");
			return (-1);
		}
		printf("Thread number %d has started\n", i);
		i++;
	}
	return (0);
}

// Join the threads represented as philosophers
// Return 0 if it succeeded
int	join_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(data->ph[i], NULL) != 0)
		{
			printf("Error: Couldn't join the thread.");
			return (-1);
		}
		printf("Thread number %d has finished\n", i);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;

	if (check_arguments(ac))
		return (1);
	init_data(ac, av, &data);
	// pthread_mutex_init(&data.mutex, NULL);
	if (create_philosophers(&data))
		return (1);
	if (join_philosophers(&data))
		return (1);
	// pthread_mutex_destroy(&data.mutex);
	return (0);
}
