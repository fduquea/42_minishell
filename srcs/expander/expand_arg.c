/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:12:11 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/13 20:03:09 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Finds and hands the dollar sign
*/
int	find_dollar(t_shell *sh, int point, char *tmp, char **line)
{
	char	*key;
	char	*env_value;

	if (tmp[1] == '?')
		return (expand_free(ft_itoa(g_exit), point, point + 2, line));
	else if (tmp[1])
	{
		sh->len = 1;
		while (ft_isalpha(tmp[sh->len]) || tmp[sh->len] == '_')
			sh->len++;
		sh->len += (ft_isalnum(tmp[sh->len]) > 0);
		while (sh->len > 2 && (ft_isalnum(tmp[sh->len]) || tmp[sh->len] == '_'))
			sh->len++;
		key = ft_substr(tmp, 1, sh->len - 1);
		env_value = get_env_value(sh, key);
		if (env_value != NULL)
			expand_valid_env(point, sh, env_value, line);
		else
			handle_invalid_env(point, sh->len, line);
		free(key);
		return (1);
	}
	return (0);
}

/*
**	Checks if there are open quotes
*/
int	check_quotes_str(const char *str, t_shell *sh)
{
	int		quotes;
	char	quote;

	quotes = 0;
	while (*str && (quotes % 2 == 0 || quotes == 0))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			quotes++;
			while (*str && *str != quote)
				str++;
			if (*str && *str == quote)
				quotes++;
		}
		if (*str)
			str++;
	}
	if (quotes % 2 != 0)
	{
		ft_putstr_fd("minishell: Open quote error.\n", 2);
		reset_loop(sh);
	}
	return (quotes);
}

/*
**	Searches for the dollar sign outside single quotes
*/
void	env_expand_dollar(t_shell *sh, char *tmp, char **line)
{
	sh->index->dquote = 0;
	sh->index->squote = 0;
	while (*(++tmp))
	{
		if (*tmp == '"' && !sh->index->squote)
			sh->index->dquote = !sh->index->dquote;
		if (*tmp == '\'' && !sh->index->dquote)
			sh->index->squote = !sh->index->squote;
		if (*tmp == '$' && !ft_strchr(NOT_EXPRESSION, *(tmp + 1)) \
		&& !sh->index->squote && \
		!((sh->index->dquote || sh->index->squote) \
		&& (*(tmp + 1) == '"' || *(tmp + 1) == '\'')))
		{
			if (find_dollar(sh, tmp - *line, tmp, line))
			{
				if (sh->index->j == -1)
					return ;
				tmp = *line - 1;
				sh->index->dquote = 0;
				sh->index->squote = 0;
			}
		}
	}
	check_quotes_str(*line, sh);
}

/*
*split cmds if expander tries to execute command
*/
void	update_cmds(t_shell *sh, char *value, char **line)
{
	int		i;
	char	**words;

	i = -1;
	free(*line);
	words = ft_split(value, ' ');
	free(*sh->cmds);
	*sh->cmds = ft_calloc(ft_countwords(value, ' ') + 1, sizeof(char *));
	while (words[++i])
		(*sh->cmds)[i] = ft_strdup(words[i]);
	free_matrix(words);
	sh->index->j = -1;
}
