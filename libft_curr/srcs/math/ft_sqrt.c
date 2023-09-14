/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:28:21 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/29 12:03:36 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <math.h>
** SYNOPSIS: square root function
**
** DESCRIPTION:
** 		The sqrt() function compute the non-negative square root of x.
*/

double	ft_sqrt(double x)
{
	double	n;

	n = 1;
	if (x > 0)
	{
		while (n * n <= x)
		{
			if (n * n == x)
				return (n);
			n++;
		}
	}
	return (0);
}
