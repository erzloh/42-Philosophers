/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:18:22 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/16 15:18:18 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data			data;

	if (check_arguments(ac, av))
		return (1);
	if (init_data(ac, av, &data))
		return (error_exit(&data, 1));
	if (create_threads(&data))
		return (error_exit(&data, 2));
	check_philos(&data);
	if (join_threads(&data))
		return (error_exit(&data, 3));
	free_memory(&data);
	return (0);
}
