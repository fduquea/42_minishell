/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:00:02 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/29 11:26:23 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: locate byte in byte string
**
** DESCRIPTION:
** 		The memchr() function locates the first occurrence of c (converted to an
**	unsigned char) in string s.
*/

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char		*str_cpy;
	size_t				i;

	i = 0;
	str_cpy = (unsigned char *)str;
	while (i < n)
	{
		if (str_cpy[i] == (unsigned char) c)
		{
			return (str_cpy + i);
		}
		i++;
	}
	return (NULL);
}
