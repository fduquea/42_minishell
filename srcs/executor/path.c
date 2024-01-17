/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:03:01 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/18 17:20:05 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* checks if the command is a path or export */
bool	check_cmds(t_shell *sh, char **cmds)
{
	char	*path;

	path = NULL;
	if (strn_strl_cmp(cmds[0], "export"))
		return (true);
	if (!cmds[0][0])
		handle_command_not_found(sh, cmds[0]);
	if (is_absolute_path(cmds[0]))
		path = ft_strdup(cmds[0]);
	else
		path = find_path(cmds[0], sh);
	if (!path)
	{
		return (false);
	}
	if (path)
		free(path);
	return (true);
}

int	is_absolute_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (1);
	}
	return (0);
}

char	*search_executable(char *cmd, char *path_env)
{
	char	*token; 
	char	*full_path;
	char	*full_path2;

	token = ft_strtok(path_env, ":");
	while (token != NULL)
	{
		full_path = ft_strjoin(token, "/");
		full_path2 = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!access(full_path2, X_OK) && !access(full_path2, F_OK))
			return (full_path2);
		free(full_path2);
		token = ft_strtok(NULL, ":");
	}
	if (!access(cmd, X_OK) && !access(full_path2, F_OK))
		return (cmd);
	return (NULL);
}

char	*find_path(char *cmd, t_shell *shell)
{
	char	*path_env;
	char	*full_path; 

	path_env = get_env_value(shell, "PATH");
	if (path_env == NULL)
		return (NULL);
	full_path = search_executable(cmd, path_env);
	free(path_env);
	return (full_path);
}
