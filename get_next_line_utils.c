/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:47:49 by kkoval            #+#    #+#             */
/*   Updated: 2023/12/30 17:51:47 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = ft_strnull();
		if (s1 == NULL)
			return (NULL);
	}
	i = 0;
	j = 0;
	ptr = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!ptr)
		return (true_free(&s1));
	while (s1[i])
		ptr[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}

char	*ft_strnull(void)
{
	char	*str_null;

	str_null = (char *)malloc(sizeof(char) * 1);
	if (!str_null)
		return (NULL);
	str_null[0] = '\0';
	return (str_null);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0' && s[i] == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	lenght_s;

	sub = NULL;
	i = 0;
	lenght_s = ft_strlen((char *) s);
	if (start + len < lenght_s)
		sub = malloc(sizeof(char) * (len + 1));
	else if (start > lenght_s)
		return (NULL);
	else
		sub = malloc(sizeof(char) * (lenght_s - start + 1));
	if (!sub)
		return (NULL);
	while (s[start + i] != '\0' && start < lenght_s && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
