/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:18:22 by eholzer           #+#    #+#             */
/*   Updated: 2023/02/21 13:05:26 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function executed by the thread
void	*routine()
{
	printf("thread is created\n");
	return (0);
}

// Create the threads represented as philosophers
// Return 0 if it succeeded
int	create_philosophers(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(pthread_t) * data->philo_nb);
	if (!data->philo)
	{
		printf("Error: malloc() couldn't allocate memory.");
		return (-1);
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philo[i], NULL, &routine, NULL) != 0)
		{
			printf("Error: Couldn't create the thread.");
			return (-1);
		}
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
		if (pthread_join(data->philo[i], NULL) != 0)
		{
			printf("Error: Couldn't join the thread.");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	check_arguments(ac);
	init_data(ac, av, &data);
	if (create_philosophers(&data))
		return (1);
	if (join_philosophers(&data))
		return (1);
	return (0);
}
