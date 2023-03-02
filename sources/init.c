/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:59:08 by eholzer           #+#    #+#             */
/*   Updated: 2023/03/02 15:43:13 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Check that the number of arguments is correct
int	check_arguments(int ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: Enter the arguments as follow: ");
		printf("./program <number_of_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> ");
		printf("optional:<number_of_times_each_philosopher_must_eat>\n");
		return (-1);
	}
	return (0);
}

int	init_philo(t_data *data_ptr)
{
	int		i;
	t_ph	*ph;

	i = 0;
	ph = malloc(sizeof(t_ph) * data_ptr->philo_nb);
	if (ph == NULL)
		return (1);
	while (i < data_ptr->philo_nb)
	{
		ph[i].id = i;
		ph[i].data_ptr = data_ptr;
		i++;
	}
	data_ptr->ph = ph;
	return (0);
}

// Initialize the data struct with the program's arguments
int	init_data(int ac, char **av, t_data *data_ptr)
{
	data_ptr->philo_nb = ft_atoi(av[1]);
	data_ptr->fork = malloc(sizeof(int) * data_ptr->philo_nb);
	if (data_ptr->fork == NULL)
		return (1);
	data_ptr->time_to_die = ft_atoi(av[2]);
	data_ptr->time_to_eat = ft_atoi(av[3]);
	data_ptr->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data_ptr->meals_nb = ft_atoi(av[5]);
	else
		data_ptr->meals_nb = -1;
	gettimeofday(&data_ptr->curr_time, NULL);
	data_ptr->init_time = data_ptr->curr_time.tv_usec;
	pthread_mutex_init(&data_ptr->mutex, NULL);
	if (init_philo(data_ptr) != 0)
		return (1);
	return (0);
}
