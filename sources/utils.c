/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:12:05 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/08 14:54:41 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_timestamp(t_data *data)
{
	long int	sec;
	long int	usec;
	long int	timestamp;

	gettimeofday(&data->curr_time, NULL);
	sec = data->curr_time.tv_sec - data->init_sec;
	usec = data->curr_time.tv_usec - data->init_usec;
	timestamp = (sec * 1000) + (usec / 1000);
	return (timestamp);
}

void	free_memory(t_data *data)
{
	if (data->fork)
		free(data->fork);
	free(data->ph);
}

int	error_exit(t_data *data, int error_code)
{
	if (error_code == 1)
		printf("An error occured with malloc()\n");
	free_memory(data);
	return (error_code);
}
