/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:00:40 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/27 16:46:48 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Changes the current directory to
** the home directory when called
*/
int	change_to_home_tilde(t_shell *shell)
{
	char	*home;

	home = get_env_value(shell, "HOME");
	if (chdir(home) == -1)
	{
		if (!home)
		{
			chdir(shell->home);
			change_env_value(shell, "PWD", shell->home);
		}
		else
			return (error_4s("cd: ", home, ": ", strerror(errno)));
	}
	else
		change_env_value(shell, "PWD", home);
	if (home)
		free(home);
	return (0);
}

/*
**	Changes the current directory to
** the home directory when called
*/
int	change_to_home(t_shell *shell)
{
	char	*home;

	home = get_env_value(shell, "HOME");
	if (chdir(home) == -1)
	{
		if (!home)
			return (error_4s("cd: ", "HOME not set", "", ""));
		else
			return (error_4s("cd: ", home, ": ", strerror(errno)));
	}
	else
		change_env_value(shell, "PWD", home);
	if (home)
		free(home);
	return (0);
}

/*
**	Checks if there are no arguments or the first argument is ~,
** if so, changes the current directory to the home directory,
** else, does nothing.
*/
bool	is_home(t_shell *shell, char **cmds)
{
	if (cmds && ft_strlen_2d(cmds) == 1)
	{
		change_to_home(shell);
		return (true);
	}
	if (cmds && (strn_strl_cmp(cmds[1], "~") == true))
	{
		change_to_home_tilde(shell);
		return (true);
	}
	return (false);
}

/*
**	Updates the PWD env variable to the current directory
*/
int	update_env_pwd(t_shell *shell)
{
	char	*path;

	path = NULL;
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (error_4s("getcwd error: ", "", "", strerror(errno)));
	change_env_value(shell, "PWD", path);
	free(path);
	path = NULL;
	return (0);
}

/*
**	Executes the cd command when called,
** if there are no arguments or the single argument is '~',
** changes the current directory to the home directory,
** if there is one argument, changes the current directory to the argument,
** if there are more than one argument, returns an error.
*/
int	builtin_cd(t_shell *shell, char **cmds)
{
	char	*old_pwd;

	if (is_home(shell, cmds) == true)
		return (0);
	if (ft_strlen_2d(cmds) > 2)
	{
		shell->index->i = 2;
		while (cmds[shell->index->i])
		{
			cmds[1] = ft_strjoin_gnl(cmds[1], " ");
			cmds[1] = ft_strjoin_gnl(cmds[1], cmds[shell->index->i++]);
		}
	}
	if (cmds[1][0] && chdir(cmds[1]) == -1)
	{
		if (cmds[2])
			return (error_4s("cd: ", "too many arguments", "", ""));
		else
			return (error_4s("cd: ", cmds[1], ": ", strerror(errno)));
	}
	else
	{
		old_pwd = get_env_value(shell, "PWD");
		change_env_value(shell, "OLDPWD", old_pwd);
		free(old_pwd);
		update_env_pwd(shell);
	}
	return (0);
}
