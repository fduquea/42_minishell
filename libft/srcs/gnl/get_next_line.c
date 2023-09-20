/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:04:28 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/21 12:40:01 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_gnl(char *static_buffer, char *temp)
{
	char	*dest;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!static_buffer)
	{
		static_buffer = malloc(sizeof(char) * 1);
		static_buffer[0] = '\0';
	}
	len = ft_strlen(static_buffer) + ft_strlen(temp) + 1;
	dest = malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	while (static_buffer[++i])
		dest[i] = static_buffer[i];
	while (temp[++j])
		dest[i + j] = temp[j];
	dest[i + j] = '\0';
	free(static_buffer);
	return (dest);
}

static char	*ft_firstline(char *string)
{
	char	*firstline;
	size_t	i;
	size_t	j;

	i = 0;
	if (!string)
		return (NULL);
	while (string[i] && string[i] != '\n')
		i++;
	firstline = malloc(sizeof(char) * (i + 2));
	if (!firstline)
		return (NULL);
	j = -1;
	while (++j <= i)
		firstline[j] = string[j];
	firstline[j] = '\0';
	return (firstline);
}

static char	*ft_secondline(char *string)
{
	char	*secondline;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (!string[i])
	{
		free(string);
		return (NULL);
	}
	len = ft_strlen(string);
	secondline = malloc(sizeof(char) * (len - i));
	if (!secondline)
		return (NULL);
	j = -1;
	while (++i < len)
		secondline[++j] = string[i];
	secondline[++j] = '\0';
	free(string);
	return (secondline);
}

static char	*get_line_and_next_one(int fd, char *static_buffer)
{
	int		bytes_read;
	char	*temp;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(static_buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			free(static_buffer);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		static_buffer = ft_strjoin_gnl(static_buffer, temp);
	}
	free(temp);
	if (ft_strlen(static_buffer) != 0)
		return (static_buffer);
	free(static_buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*static_buffer[FOPEN_MAX];
	char			*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	static_buffer[fd] = get_line_and_next_one(fd, static_buffer[fd]);
	if (!static_buffer[fd])
		return (NULL);
	return_line = ft_firstline(static_buffer[fd]);
	static_buffer[fd] = ft_secondline(static_buffer[fd]);
	return (return_line);
}
