/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:22:46 by arepsa            #+#    #+#             */
/*   Updated: 2023/11/30 17:45:45 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**  Searches for the node with the key and deletes it
*/
void	delete_env_node(t_shell *shell, char *key)
{
	t_envlst	*node_delete;
	t_envlst	*prev;
	t_envlst	*current;

	prev = NULL;
	current = shell->env_lst;
	while (current)
	{
		if (strn_strl_cmp(current->key, key) == true)
		{
			node_delete = current;
			if (prev)
				prev->next = current->next;
			else
				shell->env_lst = current->next;
			free_node_env(node_delete);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

/*
**	Deletes various envs, even if there are nonexitent inbetween
** returns prompt if there are no arguments 
** if unset PATH, still have to be able to access env (in bash /bin/env) 
*/
int	builtin_unset(t_shell *shell, char **cmds)
{
	int	i;

	i = 1;
	if (ft_strlen_2d(cmds) == 1)
		return (0);
	else
	{
		while (cmds[i])
		{
			delete_env_node(shell, cmds[i]);
			i++;
		}
		update_mini_env(shell);
	}
	return (0);
}
