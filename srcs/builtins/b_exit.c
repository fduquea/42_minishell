/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:08:24 by arepsa            #+#    #+#             */
/*   Updated: 2023/11/19 11:15:10 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	
**	Checks if the number is between the max and min 
** long long values by comparing the string
*/
static bool	islonglong(char *str)
{
	int	negative;
	int	len;

	negative = 0;
	if (*str == '-')
	{
		negative = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str == '0')
		str++;
	len = ft_strlen(str);
	if (len > 19)
		return (false);
	if (negative)
		return (ft_strncmp(str, "9223372036854775808", len) <= 0);
	else
		return (ft_strncmp(str, "9223372036854775807", len) <= 0);
}

/* 
**	Checks the first character for the sign
** and if the rest of the characters are numbers 
*/
static bool	ft_isdigit_exit(char *cmd)
{
	int	i;

	i = 0;
	if ((cmd[i] == '-' || cmd[i] == '+') && !cmd[i + 1])
		return (false);
	if ((cmd[i] == '-' || cmd[i] == '+') && cmd[i + 1])
		i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (false);
		i++;
	}
	return (true);
}

/*
**	Retrieves the exit_code from the string
** by converting it to a long long and
** using the modulo operator to get the exit code
*/
static long long	exit_standard(char *str)
{
	long long	exit_code;

	exit_code = (long long)ft_atol(str);
	if (exit_code >= 0)
		exit_code = exit_code % 256;
	else
		exit_code = 256 + (exit_code % 256);
	return (exit_code);
}

/* 
**	Shell accepts from LLONG_MIN up to LLONG_MAX to convert to exit_code
*/
void	builtin_exit(t_shell *shell, char **cmds)
{
	unsigned long long		exit_code;
	int						i;

	printf("exit\n");
	exit_code = 0;
	i = 0;
	if (ft_strlen_2d(cmds) == 1)
		exit_code = 0;
	else if (cmds[1] && (ft_isdigit_exit(cmds[1]) == false || \
		!islonglong(cmds[1])))
		exit_code = error_3s("exit: ", cmds[1], ": numeric argument required");
	else if (ft_strlen_2d(cmds) > 2)
	{
		exit_code = error_4s("exit: ", "", "", "too many arguments");
		reset_loop(shell);
	}
	else
	{
		if (cmds[1][i] == '-')
			i++;
		exit_code = exit_standard(cmds[1]);
	}
	clear_shell(shell);
	g_exit = exit_code;
	exit(exit_code);
}
