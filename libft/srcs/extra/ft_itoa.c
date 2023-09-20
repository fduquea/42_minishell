/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:36:15 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/21 11:37:47 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: convert integer to ASCII string
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns a string representing the
**	integer received as an argument. Negative numbers must be handled.
*/

#include "libft.h"

static int	ft_chrnum(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	i++;
	return (i);
}

static char	*returners(long abs_n, int charnum, char *dest, int i)
{
	while (charnum > i)
	{
		if (abs_n > 9)
		{
			dest[charnum - 1] = abs_n % 10 + 48;
			abs_n = abs_n / 10;
			charnum--;
		}
		else
		{
			dest[charnum - 1] = abs_n + 48;
			charnum--;
		}
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		charnum;
	int		j;
	int		i;
	long	abs_n;

	abs_n = n;
	i = 0;
	charnum = ft_chrnum(abs_n);
	j = charnum;
	dest = malloc(sizeof(char) * charnum + 1);
	if (!dest)
		return (NULL);
	if (abs_n < 0)
	{
		dest[0] = '-';
		i = 1;
		abs_n = -abs_n;
	}
	dest = returners(abs_n, charnum, dest, i);
	dest[j] = '\0';
	return (dest);
}
