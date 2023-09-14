/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:44:42 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/29 11:53:04 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <ctype.h>
** SYNOPSIS: punctuation character test
**
** DESCRIPTION:
** 		The ispunct() function tests for any printing character, except for
**	space (` ') or a character for which isalnum(3) is true.
*/

int	ft_ispunct(int c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96))
		return (1);
	else if (c >= 123 && c <= 126)
		return (1);
	return (0);
}
