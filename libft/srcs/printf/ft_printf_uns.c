/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:43:02 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/21 12:24:41 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*ft_uns_itoa(unsigned int n)
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

int	param_unsdecimal(unsigned int num)
{
	char	*res;
	int		buffer;

	buffer = 0;
	res = ft_uns_itoa(num);
	buffer += param_string(res);
	free (res);
	return (buffer);
}
