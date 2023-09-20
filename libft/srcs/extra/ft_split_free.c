/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:30:00 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/29 12:31:55 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: free ft_split() return pointer
**
** DESCRIPTION:
** 		The ft_split_free() function frees the memory space pointed to by s,
**		which must have been returned by a previous call to malloc() by the
**		ft_split() function.
*/

#include "libft.h"

void	ft_split_free(char **s)
{
	size_t	i;

	if (!s || !*s)
		return ;
	i = 0;
	while (i < ft_strlen_2d(s))
		free(s[i++]);
	free(s);
	*s = NULL;
}
