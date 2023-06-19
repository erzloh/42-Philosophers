/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:40:14 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/19 15:49:28 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philos(t_data *data)
{
	int	i;
	int	finished_philos;

	while (1)
	{
		i = -1;
		finished_philos = 0;
		while (++i < data->philo_nb)
		{
			if (data->ph[i].state != EATING
				&& (get_time(data) > data->ph[i].last_meal + data->time_to_die))
			{
				data->stop_simulation = true;
				printf("%ld %d has died\n", get_time(data), i);
				if (data->philo_nb == 1)
					pthread_mutex_unlock(&data->ph[0].mutex);
				return (0);
			}
			if (data->meals_nb != -1 && data->ph[i].meal >= data->meals_nb)
				finished_philos++;
		}
		if (finished_philos == data->philo_nb)
			return (data->stop_simulation = true, 0);
	}
	return (0);
}
