/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:44:58 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/29 11:54:29 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <ctype.h>
** SYNOPSIS: hexadecimal-digit character test
**
** DESCRIPTION:
** 		The isxdigit() function tests for any hexadecimal-digit character.
*/

int	ft_isxdigit(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))
		return (1);
	else if (c >= 'a' && c <= 'f')
		return (1);
	return (0);
}
