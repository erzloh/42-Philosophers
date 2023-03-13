/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:12:05 by eholzer           #+#    #+#             */
/*   Updated: 2023/03/13 11:07:25 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_timestamp(t_data *data)
{
	long int	sec;
	long int	msec;
	long int	timestamp;

	gettimeofday(&data->curr_time, NULL);
	sec = data->curr_time.tv_sec - data->init_sec;
	gettimeofday(&data->curr_time, NULL);
	if (data->curr_time.tv_usec > data->init_usec)
		msec = data->curr_time.tv_usec - data->init_usec;
	else
		msec = (1000000 - data->init_usec) + data->curr_time.tv_usec;
	timestamp = (sec * 1000) + (msec / 1000);
	return (timestamp);
}

void	free_memory(t_data *data)
{
	free(data->fork);
	free(data->ph);
}

int	error_exit(t_data *data)
{
	free_memory(data);
	return (1);
}
