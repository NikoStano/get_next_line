/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:28:48 by nistanoj          #+#    #+#             */
/*   Updated: 2025/05/19 06:02:45 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"

void	run_file(const char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error open file !");
		return ;
	}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}

int	main(int ac, char **av)
{
	int	i;

	if (ac != 2)
		return (write(1, "2 Args needed !", 15));
	i = 1;
	while (i < ac)
	{
		run_file(av[i]);
		i++;
	}
	return (0);
}

// int main(int ac, char **av)
// {
// 	(void)ac;

// 	printf("%s", get_next_line(atoi(av[1])));
// }
