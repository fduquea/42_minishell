/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:28:29 by arepsa            #+#    #+#             */
/*   Updated: 2023/11/17 11:14:47 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Checks if "-n" is present in the command
** (It can have more than one "n", e.g. "-nnnnnnn")
*/
static bool	is_no_newline(char *cmd)
{
	int	i;

	i = 2;
	if (cmd == NULL)
		return (false);
	if (ft_strncmp(cmd, "-n", 2) == 0)
	{
		while (cmd[i])
		{
			if (cmd[i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

/*
**	Account for various possible "-n" 
**	Prints commands separated by spaces
**	If "-n" is not present or there are no arguments, print newline
*/
int	builtin_echo(char **cmds)
{
	int	i;

	i = 1;
	while ((is_no_newline(cmds[i]) == true) && cmds[i])
		i++;
	while (cmds[i])
	{
		ft_putstr_fd(cmds[i], 1);
		if (cmds[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (i == 1 || is_no_newline(cmds[1]) == false)
		ft_putchar_fd('\n', 1);
	return (0);
}
