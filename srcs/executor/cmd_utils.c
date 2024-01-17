/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:11:22 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/18 17:24:26 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Gets the str until the delimiter is found "token", putting a '\0' 
in its place and storing a pointer to the position after this '\0' */
char	*ft_strtok(char *str, char *delimiter)
{
	static char	*next_token = NULL;
	char		*token;

	if (str != NULL)
		next_token = str;
	if (next_token == NULL || *next_token == '\0')
		return (NULL);
	while (*next_token != '\0' && ft_strchr(delimiter, *next_token) != NULL)
		next_token++;
	if (*next_token == '\0')
		return (NULL);
	token = next_token;
	while (*next_token != '\0' && ft_strchr(delimiter, *next_token) == NULL)
		next_token++;
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	return (token);
}

//check if command is a directory
bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		return (S_ISDIR(path_stat.st_mode));
	}
	return (false);
}
