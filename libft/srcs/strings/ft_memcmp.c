/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:08:38 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/29 11:26:34 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: compare byte string
**
** DESCRIPTION:
** 		The memcmp() function compares byte string s1 against byte string s2.
**	Both strings are assumed to be n bytes long.
*/

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*str1_cpy;
	unsigned char	*str2_cpy;

	i = 0;
	str1_cpy = (unsigned char *) str1;
	str2_cpy = (unsigned char *) str2;
	while (i < n)
	{
		if (str1_cpy[i] != str2_cpy[i])
			return (str1_cpy[i] - str2_cpy[i]);
		i++;
	}
	return (0);
}
