/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:05:14 by nistanoj          #+#    #+#             */
/*   Updated: 2025/04/14 02:18:37 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_line(int fd, char *buffer)
{
	char	*buff;
	ssize_t	rd;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	rd = 1;
	while (rd > 0 && !ft_strchr(buffer, '\n'))
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd < 0)
		{
			free(buff);
			free(buffer);
			return (NULL);
		}
		if (rd == 0)
			break ;
		buff[rd] = '\0';
		buffer = ft_strjoin(buffer, buff);
	}
	free(buff);
	if (!buffer || ft_strlen(buffer) == 0)
		return (NULL);
	return (buffer);
}

static char	*find_line(char *buffer)
{
	char	*line;
	size_t	i;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_substr(buffer, 0, i);
	return (line);
}

static char	*new_line(char *buffer)
{
	char	*nbuffer;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	nbuffer = ft_substr(buffer, i, ft_strlen(buffer) - i);
	return (free(buffer), nbuffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = find_line(buffer[fd]);
	buffer[fd] = new_line(buffer[fd]);
	return (line);
}
