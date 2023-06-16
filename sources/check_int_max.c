/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:55:43 by eholzer           #+#    #+#             */
/*   Updated: 2023/06/16 14:54:41 by eholzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static double	power(int nb, int power)
{
	int	res;

	res = 1;
	if (power < 0)
		return (0);
	while (power-- > 0)
		res *= nb;
	return (res);
}

static const char	*skip_to_number(const char *str, int *ptr_sign)
{
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		*ptr_sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

static int	is_res_out_of_range(double res, int sign)
{
	if (res > __INT_MAX__)
	{
		if (sign == -1 && res == 2147483648)
			return (0);
		return (ERROR);
	}
	return (0);
}

double	check_int_max_atoi(const char *str)
{
	int		i;
	int		sign;
	int		*ptr_sign;
	int		nb_len;
	double	res;

	i = 0;
	sign = 1;
	ptr_sign = &sign;
	nb_len = 0;
	res = 0;
	str = skip_to_number(str, ptr_sign);
	while (str[i] >= '0' && str[i++] <= '9')
		nb_len++;
	if (nb_len > 10)
		return (ERROR);
	i = 0;
	while (i < nb_len)
	{
		res += (str[i] - '0') * power(10, nb_len - 1 - i);
		if (is_res_out_of_range(res, sign))
			return (ERROR);
		i++;
	}
	return (0);
}
