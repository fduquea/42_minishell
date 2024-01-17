/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:48:02 by arepsa            #+#    #+#             */
/*   Updated: 2023/11/17 11:22:32 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Prints all the env variables that contain a value
*/
void	print_env_list(t_shell *shell)
{
	t_envlst	*current;

	current = shell->env_lst;
	while (current != NULL)
	{
		if (current->visible != 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

/*
**	Executes the env command
*/
int	builtin_env(t_shell *shell, char **cmds)
{
	if (ft_strlen_2d(cmds) > 1)
		return (short_error("env: '", cmds[1], "': No such" \
		"file or directory", 127));
	else
		print_env_list(shell);
	return (0);
}
