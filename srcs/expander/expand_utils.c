/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:14:23 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/13 20:02:53 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_empty(char **cmds, int nbr_cmds)
{
	int	i;
	int	j;
	int	empty;

	empty = nbr_cmds;
	i = 0;
	j = 0;
	while (i < nbr_cmds)
	{
		if (cmds[i] != NULL)
		{
			cmds[j++] = cmds[i];
			empty--;
		}
		i++;
	}
	cmds[j] = NULL;
	return (empty);
}

/*
** Expands the commands replacing "line" with the "key".
** It starts replacing at "i" and ends at "j"
*/
int	expand_cmds(char *key, int i, int j, char **line)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(*line, 0, i);
	tmp2 = ft_substr(*line, j, ft_strlen(*line) - j + 1);
	free(*line);
	*line = ft_strjoin_gnl(tmp, key);
	*line = ft_strjoin_gnl(*line, tmp2);
	free(tmp2);
	return (1);
}

/*
**	Expands an invalid env, replacing it with ""
*/
void	handle_invalid_env(int point, int len, char **line)
{
	char	*env_value;

	env_value = "\0";
	expand_cmds(env_value, point, point + len, line);
}

/*
**	Expands an existing env to its value
*/
void	expand_valid_env(int start, t_shell *sh, char *env_value, char **line)
{
	char	*tmp;

	tmp = ft_substr(*line, start + sh->len, \
		ft_strlen(*line) - start + sh->len + 1);
	if (sh->index->dquote)
		expand_cmds(env_value, start, start + sh->len, line);
	else if (ft_countwords(env_value, ' ') > 1 && !start && !tmp[0] && \
	ft_strlen_2d(*sh->cmds) == 1)
		update_cmds(sh, trim_whitespace(sh, env_value), line);
	else
		expand_cmds(trim_whitespace(sh, env_value), start, \
									start + sh->len, line);
	free(tmp);
	free(env_value);
}

/*
**  Expand_cmds and free the key
*/
int	expand_free(char *key, int i, int j, char **line)
{
	expand_cmds(key, i, j, line);
	free(key);
	return (1);
}
