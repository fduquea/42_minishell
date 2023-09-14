/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:05:59 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/21 12:26:44 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_len(unsigned int num)
{
	int	i;

	i = 0;
	while (num >= 16)
	{
		num /= 16;
		i++;
	}
	i++;
	return (i);
}

static void	ft_print_hex(unsigned int num, const char c)
{
	if (num >= 16)
	{
		ft_print_hex(num / 16, c);
		ft_print_hex(num % 16, c);
	}
	else
	{
		if (num <= 9)
			ft_putchar(num + '0');
		else
		{
			if (c == 'x')
				ft_putchar(num - 10 + 'a');
			else if (c == 'X')
				ft_putchar(num - 10 + 'A');
		}
	}
}

int	param_hex(unsigned int num, char c)
{
	ft_print_hex(num, c);
	return (hex_len(num));
}
