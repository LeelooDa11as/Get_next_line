/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:03:32 by kkoval            #+#    #+#             */
/*   Updated: 2023/12/18 19:03:35 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	char	*buff;
	int		len_chrs;
	int		i;

	buff = malloc(sizeof(char) * 7);
	if (!buff)
		return (NULL);

	len_chrs = read(fd, buff, 5);
	while (len_chrs > 0)
	{
		i = 0;
		printf("%s\n", buff);
		while(i < len_chrs)
		{
			if(buff[i] == '\n')
			{
				buff[i] = '\0';
				printf("tengo que parar");
				return(buff);
			}
			i++;
			printf("no he parado");
		}
		len_chrs = read(fd, buff, 5);
	}
	if (len_chrs == -1) 
		return (NULL);
	buff[len_chrs - 1] = '\0';
	return (buff);
}

int	main(void)
{
	int		fd;

	fd = open("borja.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	return(1);
}
