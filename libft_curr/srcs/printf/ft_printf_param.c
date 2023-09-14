/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:33:14 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/21 12:27:22 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	param_string(char *string)
{
	int		i;

	i = 0;
	if (!string)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*string)
	{
		write(1, string, 1);
		string++;
		i++;
	}
	return (i);
}

int	param_pointer(unsigned long long ptr)
{
	char			hex[20];
	char			*base;
	int				i;
	int				ret;

	hex[12] = '\0';
	i = 0;
	base = "0123456789abcdef";
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	while (ptr)
	{
		hex[i++] = base[ptr % 16];
		ptr /= 16;
	}
	ret = i + 2;
	while (i--)
		write(1, &hex[i], 1);
	return (ret);
}

int	param_decimal(int num)
{
	char	*res;
	int		buffer;

	buffer = 0;
	res = ft_itoa(num);
	buffer += param_string(res);
	free (res);
	return (buffer);
}
