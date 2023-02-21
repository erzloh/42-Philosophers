/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:59:08 by eholzer           #+#    #+#             */
/*   Updated: 2023/02/21 13:00:34 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Check that the number of arguments is correct
void	check_arguments(int ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: Enter the arguments as follow: ");
		printf("./program <number_of_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> ");
		printf("optional:<number_of_times_each_philosopher_must_eat>\n");
		exit(1);
	}
}

// Initialize the data struct with the program's arguments
void	init_data(int ac, char **av, t_data *data)
{
	data->philo_nb = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_nb = ft_atoi(av[5]);
	else
		data->meals_nb = -1;
}