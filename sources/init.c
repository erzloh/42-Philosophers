/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:59:08 by eholzer           #+#    #+#             */
/*   Updated: 2023/03/07 17:02:38 by eholzer          ###   ########.fr       */
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

int	init_philo(t_data *data)
{
	int		i;
	t_ph	*ph;

	i = 0;
	ph = malloc(sizeof(t_ph) * data->philo_nb);
	if (ph == NULL)
		return (1);
	while (i < data->philo_nb)
	{
		ph[i].id = i;
		ph[i].data = data;
		pthread_mutex_init(&ph[i].mutex, NULL);
		i++;
	}
	data->ph = ph;
	return (0);
}

// Initialize the data struct with the program's arguments
int	init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = -1;
	data->philo_nb = ft_atoi(av[1]);
	data->fork = malloc(sizeof(int) * data->philo_nb);
	if (data->fork == NULL)
		return (1);
	while (++i < data->philo_nb)
		data->fork[i] = 1;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_nb = ft_atoi(av[5]);
	else
		data->meals_nb = -1;
	gettimeofday(&data->curr_time, NULL);
	data->init_sec = data->curr_time.tv_sec;
	data->init_usec = data->curr_time.tv_usec;
	if (init_philo(data) != 0)
		return (1);
	return (0);
}
