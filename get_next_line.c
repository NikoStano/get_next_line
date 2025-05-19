/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:33:41 by nistanoj          #+#    #+#             */
/*   Updated: 2025/05/19 07:20:04 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buffer)
{
	char	file[BUFFER_SIZE + 1];
	ssize_t	rd;

	rd = 1;
	while (rd > 0 && !ft_strchr(buffer, '\n'))
	{
		rd = read(fd, file, BUFFER_SIZE);
		if (rd == -1)
			return (free(buffer), NULL);
		file[rd] = '\0';
		buffer = ft_strjoin(buffer, file);
		if (!buffer)
			buffer = ft_strdup("");
	}
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

static char	*next_line(char *buffer)
{
	char	*next;
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
	next = ft_substr(buffer, i, ft_strlen(buffer) - i);
	return (free(buffer), next);
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
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	buffer = next_line(buffer);
	return (line);
}
