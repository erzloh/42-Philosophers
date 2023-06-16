/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:57:33 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/16 15:25:48 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_alpha(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_int_max(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_int_max_atoi(av[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// Check that the number of arguments is correct
int	check_arguments(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: Enter the arguments as follow: ");
		printf("./program <number_of_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> ");
		printf("optional:<number_of_times_each_philosopher_must_eat>\n");
		return (1);
	}
	else if (check_alpha(av) == 1)
	{
		printf("Error: only whole number inputs are valid.\n");
		return (1);
	}
	else if (check_int_max(av))
	{
		printf("Error: input can't exceed the int max value.\n");
		return (1);
	}
	return (0);
}
