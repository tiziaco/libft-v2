/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:27:30 by tiacovel          #+#    #+#             */
/*   Updated: 2024/02/14 16:06:35 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_buffer(char *stach, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(stach, buffer);
	free(stach);
	return (tmp);
}

static char	*fill_stach(int fd, char *stach)
{
	char	*buffer;
	int		bytes_read;

	if (!stach)
		stach = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(stach);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stach = join_buffer(stach, buffer);
		if (ft_strchr(stach, '\n') != NULL)
			break ;
	}
	free(buffer);
	return (stach);
}

static char	*get_tail(char *stach)
{
	char	*next_stach;
	int		i;
	int		j;

	i = 0;
	while (stach[i] && stach[i] != '\n')
		i++;
	if (!stach[i])
	{
		free(stach);
		return (NULL);
	}
	next_stach = ft_calloc(ft_strlen(stach) - i + 1, sizeof(char));
	i++;
	j = 0;
	while (stach[i])
		next_stach[j++] = stach[i++];
	free(stach);
	return (next_stach);
}

static char	*fill_line(char *stach)
{
	char	*line;
	int		i;

	i = 0;
	if (!stach[i])
		return (NULL);
	while (stach[i] && stach[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stach[i] && stach[i] != '\n')
	{
		line[i] = stach[i];
		i++;
	}
	if (stach[i] && stach[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stach;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	stach = fill_stach(fd, stach);
	if (!stach)
		return (NULL);
	next_line = fill_line(stach);
	stach = get_tail(stach);
	return (next_line);
}

/* #include <fcntl.h>
#include <stdio.h>
int main (void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDWR);
	if (fd == -1)
		printf("Error opening the file!!");

	for (size_t i = 0; i < 12; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	
	close(fd);

	return (0);
} */
