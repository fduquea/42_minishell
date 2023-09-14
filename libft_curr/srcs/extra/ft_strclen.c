/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:13:07 by fduque-a          #+#    #+#             */
/*   Updated: 2023/07/03 21:17:52 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: Find number of characters before a given character
**
** DESCRIPTION:
** 		The ft_strclen() function computes the length of the string s,
** 	but stops when there's the occurrence of the character c.
*/

#include "libft.h"

size_t	ft_strclen(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s && s[len] != c && s[len])
		len++;
	return (len);
}
