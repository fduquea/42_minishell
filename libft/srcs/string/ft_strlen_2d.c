/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:28:57 by fduque-a          #+#    #+#             */
/*   Updated: 2023/09/20 11:38:41 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: find length of two dimensional array
**
** DESCRIPTION:
** 		The strlen_2d() function computes the length of the two dimensional
**		array s.
*/

#include "libft.h"

size_t	ft_strlen_2d(char **s)
{
	size_t	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}
