/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:58:31 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/19 13:08:28 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	unlock_mutexes(t_data *data, t_ph *ph)
{
	pthread_mutex_unlock(&ph->mutex);
	if (data->philo_nb != 1)
		pthread_mutex_unlock(&data->ph[(ph->id + 1) % data->philo_nb].mutex);
	return (-1);
}
