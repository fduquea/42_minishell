/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_use.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:54:02 by arepsa            #+#    #+#             */
/*   Updated: 2023/11/21 12:44:48 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Counts the number of nodes in the linked list
*/
int	ft_list_size_env(t_envlst *list)
{
	int	size;

	size = 0;
	while (list != NULL)
	{
		list = list->next;
		size++;
	}
	return (size);
}

/*
**	This function adds a variable to the array
*/
void	join_mini_env(t_envlst *env_lst, char **mini_env, int i)
{
	if (env_lst->visible)
	{
		mini_env[i] = ft_strjoin_gnl(mini_env[i], env_lst->key);
		if (env_lst->value)
		{
			mini_env[i] = ft_strjoin_gnl(mini_env[i], "=");
			mini_env[i] = ft_strjoin_gnl(mini_env[i], env_lst->value);
		}
	}
}

/*
**	Overwrite the env array in the main structure with data from 
** env linked list, ignore empty envs
*/
void	update_mini_env(t_shell *shell)
{
	t_envlst	*head;
	int			size;
	int			i;

	size = ft_list_size_env(shell->env_lst);
	if (shell->mini_env)
		free_matrix(shell->mini_env);
	if (!shell->env_lst)
	{
		shell->mini_env = NULL;
		return ;
	}
	shell->mini_env = ft_calloc(1, sizeof(char *) * (size + 1));
	head = shell->env_lst;
	i = 0;
	shell->mini_env[i] = NULL;
	while (shell->env_lst)
	{
		join_mini_env(shell->env_lst, shell->mini_env, i);
		i++;
		shell->env_lst = shell->env_lst->next;
	}
	shell->env_lst = head;
}

/* 
**	Returns string that contains the value of the key
** that is passed as a parameter
** free "value" after using, strdup uses malloc
*/
char	*get_env_value(t_shell *shell, char *key)
{
	t_envlst	*head;
	char		*value;

	head = shell->env_lst;
	value = NULL;
	while (shell->env_lst)
	{
		if (strn_strl_cmp(key, shell->env_lst->key) && shell->env_lst->visible)
		{
			value = ft_strdup(shell->env_lst->value);
			break ;
		}
		shell->env_lst = shell->env_lst->next;
	}
	shell->env_lst = head;
	return (value);
}

/*
**	Changes the value of the requested key
*/
int	change_env_value(t_shell *shell, char *key, char *new_value)
{
	t_envlst	*head;

	head = shell->env_lst;
	while (shell->env_lst)
	{
		if (strn_strl_cmp(key, shell->env_lst->key) == true)
		{
			if (shell->env_lst->value)
				free(shell->env_lst->value);
			shell->env_lst->value = ft_strdup(new_value);
			if (shell->env_lst->visible == 0)
				shell->env_lst->visible = 1;
			shell->env_lst = head;
			update_mini_env(shell);
			return (1);
		}
		shell->env_lst = shell->env_lst->next;
	}
	shell->env_lst = head;
	return (0);
}
