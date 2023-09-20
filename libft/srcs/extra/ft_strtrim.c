/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:17:18 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/21 12:52:52 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: trim beginning and end of string with the specified characters
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns a copy of ’s1’ with the
**	characters specified in ’set’ removed from the beginning and the end of the
**	string.
*/

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (len - 1 > i && ft_strchr(set, s1[len - 1]))
		len--;
	if (i > len - 1 || !set)
		return (ft_strdup(""));
	dest = (char *)malloc(len - i + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1 + i, len - i + 1);
	return (dest);
}
