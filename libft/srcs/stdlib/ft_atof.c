/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:22:46 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/21 12:41:10 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <stdlib.h>
** SYNOPSIS: convert ASCII string to double
**
** DESCRIPTION:
** 		The atof() function converts the initial portion of the string pointed
**	to by str to double representation.
*/

#include <math.h>

double	ft_atof(char *str)
{
	double	res_bef;
	double	res_aft;
	double	sign;
	int		i;

	i = 0;
	res_aft = 0.0;
	res_bef = 0.0;
	sign = 1.0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1.0;
	while (*str >= 0 && *str <= 9)
		res_bef = res_bef * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
	{
		while (*str >= 0 && *str <= 9)
			res_aft += (pow(10, i--) * (*str++ - '0'));
	}
	return (sign * (res_bef + res_aft));
}
