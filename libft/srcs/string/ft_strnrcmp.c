/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:37:29 by fduque-a          #+#    #+#             */
/*   Updated: 2023/07/03 15:58:47 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: reversely compare strings (size-bounded)
**
** DESCRIPTION:
** 		The strnrcmp() function lexicographically compare the null-terminated
**	strings s1 and s2.
** 		The strnrcmp() function reversely compares not more than n characters.
**	Because strnrcmp() is designed for comparing strings rather than binary
**	data, characters that appear after a `\0' character are not compared.
*/

#include "libft.h"

int	ft_strnrcmp(char *s1, char *s2, size_t n)
{
	int	i;
	int	j;

	if (n == 0)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	while (s1[i] == s2[j] && i >= 0 && j >= 0)
	{
		n--;
		if (n == 0)
			return (0);
		i--;
		j--;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[j]));
}
