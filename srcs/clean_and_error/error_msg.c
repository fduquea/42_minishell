/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:34:09 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/13 19:47:54 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
**	Output error message and return error number
** always starts with "minishell: "
** has space for 3 input strings
*/
int	error_3s(char *str1, char *str2, char *str3)
{
	g_exit = 1;
	if (!ft_strncmp(str3, ": numeric argument required", 27))
		g_exit = 2;
	write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	return (g_exit);
}

/* 
**	Output error message and return error number
** always starts with "minishell: "
** has space for 4 string inputs
*/
int	error_4s(char *str1, char *str2, char *str3, char *str4)
{
	g_exit = 1;
	if (!ft_strncmp(str4, "numeric argument required", 25))
		g_exit = 2;
	write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, str3, ft_strlen(str3));
	write(2, str4, ft_strlen(str4));
	write(2, "\n", 1);
	return (g_exit);
}

/*
**	Excludes 'minishell:', max 3 strings
*/
int	short_error(char *str1, char *str2, char *str3, int exit_no)
{
	g_exit = exit_no;
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	return (g_exit);
}
