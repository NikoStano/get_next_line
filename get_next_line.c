/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:33:41 by nistanoj          #+#    #+#             */
/*   Updated: 2025/05/11 19:57:14 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buffer)
{
	char	*buff;
	ssize_t	rd;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	rd = 1;
	while (rd > 0 && !ft_strchr(buffer, '\n'))
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
			return (free(buff), free(buffer), NULL);
		buff[rd] = '\0';
		buffer = ft_strjoin(buffer, buff);
	}
	return (free(buff), buffer);
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
	char	*new;
	size_t	i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	new = ft_substr(buffer, i, ft_strlen(buffer) - i);
	return (free(buffer), new);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = find_line(buffer);
	buffer = new_line(buffer);
	return (line);
}
