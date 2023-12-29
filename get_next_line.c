/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:03:32 by kkoval            #+#    #+#             */
/*   Updated: 2023/12/28 21:38:23 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


//Esta funcion coje el storage y mira donde termina el primer \n o \0 para calcular
//cuanto mide el resto, hacer un malloc , i copiar alli, lo que devemos guardar. 
//aqui preparamos la siguiente linea
char *clean_storage(char *storage)
{
	char	*new_storage;
	size_t	start;
	size_t	len;

	start = 0;
	len = ft_strlen(storage);
	while(storage[start] != '\n' && storage[start] != '\0')
		start++;
	new_storage = ft_substr(storage, (unsigned int)start, len); //por que +1??
	//new_storage = ft_strchr(storage, '\n'); ---> es equivalente o todo lo anterior???
	return new_storage;
}


//Esta funcion coje el storage y mira donde esta el primer \n o \0 para saber
//cual sera la longitud de la linea, haremos un malloc, copiaremos la linea, y nos devolveremos 
//ese malloc
//cogemos la linea para devolver
char *take_line(char *storage)
{
	char	*line;
	size_t	size;

	size = 0;
	while(storage[size] != '\n' && storage[size] != '\0')
		size++;
	line = ft_substr(storage, 0, size);
	return (line);
}


//La mision de esta funcion, es ir copiando bloque de BUFFERSIZE a storage
//hasta que stroage tenag suficiente informacion como para poder LUEGO extraer una linea
//o hayamos llegado al final del archivo
char 	*fill_storage(char *storage, int fd)
{
	char	*buffer;
	int 	read_bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(storage);
			return NULL;
		}
		buffer[read_bytes] = '\0';
		storage = ft_strjoin(storage, buffer);	
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char 	*storage = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	storage = fill_storage(storage, fd);
	if (storage == NULL)
		return NULL;
	line = take_line(storage);
	if (line == NULL)
	{
		free(storage);
		return NULL;
	}
	storage = clean_storage(storage);
	return line;
}
/*
int	main(void)
{
 	int		fd;

 	fd = open("text.txt", O_RDONLY);
 	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return(1);
}*/
