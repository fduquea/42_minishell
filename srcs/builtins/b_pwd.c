/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:37:00 by arepsa            #+#    #+#             */
/*   Updated: 2023/11/17 11:22:48 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Executes the pdw command using the getcwd() function
*/
int	builtin_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (error_4s("getcwd error: ", "", "", strerror(errno)));
	printf("%s\n", pwd);
	free(pwd);
	pwd = NULL;
	return (0);
}
