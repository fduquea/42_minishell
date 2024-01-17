/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:15:21 by arepsa            #+#    #+#             */
/*   Updated: 2023/11/27 18:43:24 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Changes the env value; If no key is found,
** or the key has no value, add new env node;
** If key has no value, set it to invisible in env_list
*/
void	export_change_value(t_shell *shell, char *key, char *value, int visible)
{
	t_envlst	*env_node;

	env_node = NULL;
	if (change_env_value(shell, key, value) == 0 && visible == 1)
	{
		env_node = ft_lstnew_env(key, value, 1);
		ft_lstadd_back_env(&shell->env_lst, env_node);
	}
	else if (!value && visible == 0)
	{
		env_node = ft_lstnew_env(key, value, 0);
		ft_lstadd_back_env(&shell->env_lst, env_node);
	}
	else
	{
		free (key);
		free (value);
	}
}

/*
**	Checks if key starts with letter or '_' and
** contains only alfanumeric characters
*/
int	key_error(char *str)
{
	int		i;

	i = 1;
	if (!str || ft_strlen(str) == 0)
		return (error_4s("export: '", str, "': ", "not a valid identifier"));
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (error_4s("export: '", str, "': ", "not a valid identifier"));
	if (str[0] == '_' && (!str[1] || str[1] == '='))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (error_3s("export: '", str, "': not a valid identifier"));
		i++;
	}
	return (0);
}

/*
**	Executes export when there is an argument
*/
int	do_export(t_shell *shell, char *cmd)
{
	char	*key;
	char	*value;

	if (key_error(cmd) == 0)
	{
		key = get_key(cmd);
		value = get_value(cmd);
		if (ft_strchr(cmd, '='))
		{
			export_change_value(shell, key, value, 1);
		}
		else
			export_change_value(shell, key, value, 0);
	}
	return (0);
}

/*
**	Executes the export command checking if
** there are arguments or not
*/
int	builtin_export(t_shell *shell, char **cmds)
{
	int	i;

	i = 1;
	if (ft_strlen_2d(cmds) == 1)
		print_export(shell);
	else
	{
		while (cmds[i])
		{
			do_export(shell, cmds[i]);
			i++;
		}
		update_mini_env(shell);
	}
	return (0);
}
