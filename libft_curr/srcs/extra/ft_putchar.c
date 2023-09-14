/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:15:55 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/29 12:15:37 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <stdio.h>
** SYNOPSIS: output a character to stdout
**
** DESCRIPTION:
** 		The putchar() function writes the character c (converted to an
**	``unsigned char'') to the output stream of stdout.
** 		[42 PDF] Outputs the character ’c’ to stdout.
*/

#include "libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
