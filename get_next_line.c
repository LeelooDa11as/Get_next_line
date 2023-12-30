/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:03:32 by kkoval            #+#    #+#             */
/*   Updated: 2023/12/30 17:45:32 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Mira donde termina el primer \n o \0 para para calcular cuanto mide el resto
y copiar en new_storage lo que tenemos que guardar*/
char	*clean_storage(char *storage)
{
	char	*new_storage;
	size_t	start;
	size_t	len;

	start = 0;
	if (!storage || storage[0] == '\0')
	{
		free(storage);
		return (NULL);
	}
	len = ft_strlen(storage);
	while (storage[start] != '\n' && storage[start] != '\0')
		start++;
	if (storage[start] == '\0')
	{
		free(storage);
		return (NULL);
	}
	start++;
	new_storage = ft_substr(storage, (unsigned int)start, len);
	free(storage);
	return (new_storage);
}

char	*take_line(char *storage)
{
	char	*line;
	size_t	size;

	size = 0;
	if (storage[0] == '\0')
		return (NULL);
	while (storage[size] != '\n' && storage[size] != '\0')
		size++;
	if (storage[size] == '\n')
		size++;
	line = ft_substr(storage, 0, size);
	return (line);
}

char	*fill_storage(char *storage, int fd)
{
	char	*buffer;
	int		read_bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(storage);
		return (NULL);
	}
	buffer[0] = '\0';
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(storage);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		storage = ft_strjoin(storage, buffer);
	}
	free(buffer);
	return (storage);
}

char	*true_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = fill_storage(storage, fd);
	if (storage == NULL)
		return (NULL);
	line = take_line(storage);
	if (line == NULL)
		return (true_free(&storage));
	storage = clean_storage(storage);
	return (line);
}
