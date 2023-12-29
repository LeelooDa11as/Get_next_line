/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:03:32 by kkoval            #+#    #+#             */
/*   Updated: 2023/12/29 18:59:49 by kkoval           ###   ########.fr       */
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
	if(!storage || storage[0] == '\0')
	{
		free(storage);
		return NULL;
	}
	len = ft_strlen(storage);
	while (storage[start] != '\n' && storage[start] != '\0')
		start++;
	if(storage[start] == '\0')
	{
		free(storage);
		return NULL;
	}
	start++; // como es un \n, avanzamos uno mas
	new_storage = ft_substr(storage, (unsigned int)start, len);
	free(storage);
	return (new_storage);
}
/*Coje el storage y mira donde esta el primer \n o \0 para saber
cual sera la longitud de la linea, haremos un malloc*/
char	*take_line(char *storage)
{
	char	*line;
	size_t	size;

	size = 0;
	if (storage[0] ==  '\0')
		return NULL;
	while (storage[size] != '\n' && storage[size] != '\0')
		size++;
	if(storage[size] == '\n') //importante cojer el \n o no devolvemos la linea engtera i nos quedaremos pilaldos a la sigueinte llamada
		size++;
	line = ft_substr(storage, 0, size);
	return (line);
}
/*La mision de esta funcion, es ir copiando bloque de BUFFERSIZE a storage
hasta que stroage tenag suficiente informacion como para poder LUEGO 
extraer una linea o hayamos llegado al final del archivo*/

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

//800 -> hola que tal como estas

//(600) **ptr -> 400
char *true_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return NULL;
}

/*
//(600) **ptr -> 800
char *true_free(char *ptr)
{
	free(ptr);
	ptr = NULL;   <--- aqui no estoy poniendo en NULL el puntero storage ortiginal
				  <--- se lo estmoa poniendo al hermano tonto (ptr)
	return NULL;
}

//(400) storage -> 800;
storage = clean_storage(storage);
*/

//(400) storage -> 800;
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
	{
		/*
		free(storage);
		storage = NULL; // Esto es importante porque storage es una variable static
		// Si libero storage, la proxima vez que llaman a GNL, storage seguiria conservando la antigua
		// direccion de memoria que ya habiamos liberado, si intentamos trabajar sobre ells, segmentetion fault
		// por eso lo ponemos en NULL, y asi la proxima llamada a GNL, no iremos a visitar una zona que no existe
		return (NULL);
		*/
		return(true_free(&storage));
	}
	storage = clean_storage(storage);
	//aqui seria tarde liberar porque hemos perdido la direccion del "primer" storage
	//o tambien havcer algo como
	/*
		if(storage == NULL)
			free(storage);
	*/
	return (line);
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
