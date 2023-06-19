/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:00:28 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/19 10:51:29 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Create the threads represented as philosophers
// Return 0 if it succeeded
int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->ph[i].th, NULL, &routine, &data->ph[i]) != 0)
		{
			printf("Error: Couldn't create the thread.\n");
			return (1);
		}
		i++;
		usleep(50);
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
			printf("Error: Couldn't join the thread.\n");
			return (1);
		}
		pthread_mutex_destroy(&data->ph[i].mutex);
		i++;
	}
	return (0);
}
