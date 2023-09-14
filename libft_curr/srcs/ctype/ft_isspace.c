/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:44:25 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/29 11:53:58 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <ctype.h>
** SYNOPSIS: white-space character test
**
** DESCRIPTION:
** 		The isspace() function tests for the white-space characters.
*/

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v')
		return (1);
	else if (c == '\r' || c == '\f')
		return (1);
	return (0);
}
