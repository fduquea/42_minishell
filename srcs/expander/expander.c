/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:09:33 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/13 19:59:54 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
** add spaces if line contains pipes next to characters 
*/
void	expand_line(t_shell *sh, char *tmp)
{
	sh->index->dquote = 0;
	sh->index->squote = 0;
	while (*(++tmp))
	{
		if (*tmp == '"' && !sh->index->squote)
			sh->index->dquote = !sh->index->dquote;
		if (*tmp == '\'' && !sh->index->dquote)
			sh->index->squote = !sh->index->squote;
		if (ft_strchr("|", *tmp) && !sh->index->dquote && \
		!sh->index->squote)
		{
			if (tmp != sh->ui && !ft_strchr(WHITESPACE, *(tmp - 1)))
			{
				if (expand_cmds(" ", tmp - sh->ui, tmp - sh->ui, &sh->ui))
					tmp = sh->ui - 1;
			}
			else if (!ft_strchr(WHITESPACE, *(tmp + 1)))
			{
				if (expand_cmds(" ", tmp - sh->ui + 1, tmp - \
				sh->ui + 1, &sh->ui))
					tmp = sh->ui - 1;
			}
		}
	}
	reset_index(sh->index);
}

/*
**	Removes quotes from the argument it receives
** It also updates the length of the argument
*/
void	remove_quotes_expander(char *arg, int *len)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (i < *len)
	{
		if ((arg[i] == '"' || arg[i] == '\'') && !quote)
		{
			quote = arg[i];
			ft_memmove(arg + i, arg + i + 1, *len - i);
			(*len)--;
		}
		else if (quote && arg[i] == quote)
		{
			quote = 0;
			ft_memmove(arg + i, arg + i + 1, *len - i);
			(*len)--;
		}
		else
			i++;
	}
}

/*
**	The expander itself. It expands arguments,
** trims arguments and removes quotes
*/
void	expander(char ***cmds, t_shell *sh)
{
	sh->index->j = -1;
	if (!cmds || !cmds[0] || !cmds[0][0])
		return ;
	sh->cmds = cmds;
	while ((*cmds)[++sh->index->j])
	{
		sh->expanded = (ft_strchr((*cmds)[sh->index->j], '$') != NULL);
		env_expand_dollar(sh, (*cmds)[sh->index->j] - 1, \
		&(*cmds)[sh->index->j]);
		if (sh->index->j == -1)
			return ;
		sh->len = ft_strlen((*cmds)[sh->index->j]);
		remove_quotes_expander((*cmds)[sh->index->j], &sh->len);
		if (!(*cmds)[sh->index->j][0] && sh->expanded)
		{
			free((*cmds)[sh->index->j]);
			(*cmds)[sh->index->j] = NULL;
		}
	}
	if (remove_empty(*cmds, sh->index->j) == sh->index->j)
	{
		free(*cmds);
		*cmds = NULL;
	}
}

/*
** trims all whitespace before and after env value
** leaves one in the middle
*/
char	*trim_whitespace(t_shell *sh, char *str)
{
	int	spaces;

	spaces = 1;
	sh->index->i = 0;
	sh->index->k = 0;
	while (ft_isspace(str[sh->index->i]))
		sh->index->i++;
	sh->index->i--;
	while ((unsigned long)++sh->index->i < ft_strlen(str))
	{
		if (!ft_isspace(str[sh->index->i]))
		{
			str[sh->index->k++] = str[sh->index->i];
			spaces = 1;
		}
		else
		{
			if (spaces++ == 1)
				str[sh->index->k++] = ' ';
		}
	}
	if ((ft_isspace(str[sh->index->k - 1]) && str[sh->index->k]))
		str[sh->index->k - 1] = '\0';
	str[sh->index->k] = '\0';
	return (str);
}
