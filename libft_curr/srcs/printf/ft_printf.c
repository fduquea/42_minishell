/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:56:10 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/21 12:24:46 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	param_char(char character)
{
	write(1, &character, 1);
	return (1);
}

static int	param_detector(va_list args, char c)
{
	if (c == 'c')
		return (param_char(va_arg(args, int)));
	if (c == 's')
		return (param_string(va_arg(args, char *)));
	if (c == 'p')
		return (param_pointer(va_arg(args, unsigned long long)));
	if (c == 'd' || c == 'i')
		return (param_decimal(va_arg(args, int)));
	if (c == 'u')
		return (param_unsdecimal(va_arg(args, unsigned int)));
	if (c == 'x' || c == 'X')
		return (param_hex(va_arg(args, unsigned long long), c));
	if (c == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		n;
	int		buffer;

	va_start(args, str);
	buffer = 0;
	n = 0;
	while (str[n])
	{
		if (str[n] == '%')
		{
			n++;
			buffer += param_detector(args, str[n]);
		}
		else
		{
			write(1, &str[n], 1);
			buffer++;
		}
		n++;
	}
	va_end(args);
	return (buffer);
}
