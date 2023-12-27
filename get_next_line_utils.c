#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while(str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ptr;
	int		i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = -1;
	if (!s1 || !s2)
		return(NULL);
	ptr = (char *)malloc(sizeof(char) * ((len_s1 + len_s2 + 1)));
	if(!ptr)
		return(NULL);
	while(++i < len_s1)
		ptr[i] = s1[i];
	i = -1;
	while(++i < len_s2)
		ptr[len_s1 + i] = s2[i];
	ptr[len_s1 + len_s2] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	len;
	char	*str;

	len = ft_strlen(s);
	str = (char *)s;
	while (len >= 0)
	{
		if (str[len] == (char)c)
		{
			return (&str[len]);
		}
		len--;
	}
	return (NULL);
}


int	main(void)
{
	printf("%s\n", ft_strjoin("hello", " how you doing?"));
	return (0);
}
