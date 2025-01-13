#include "pipex.h"


char    *ft_strcpy(char *dest, char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
char    *ft_strcat(char *dest, char *src)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (dest[i])
        i++;
    while (src[j])
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return (dest);
}
// int	ft_strncmp(char *s1, char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && i < n && s1[i] == s2[i])
// 	{
// 		i++;
// 	}
// 	if (i == n)
// 		return (0);
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }
// size_t	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// static int	ft_count_subs(char const *s, char c)
// {
// 	int	count;

// 	count = 0;
// 	while (*s)
// 	{
// 		while (*s == c && *s)
// 			s++;
// 		if (*s != c && *s)
// 		{
// 			count++;
// 			while (*s != c && *s)
// 				s++;
// 		}
// 	}
// 	return (count);
// }

// static int	ft_len_subs(char const *s, char c)
// {
// 	int	len;

// 	len = 0;
// 	while (*s != c && *s)
// 	{
// 		len++;
// 		s++;
// 	}
// 	return (len);
// }

// static char	*ft_strncpy(char *dest, char const *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (src[i] != '\0' && i < n)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	while (i < n)
// 	{
// 		dest[i] = '\0';
// 		i++;
// 	}
// 	return (dest);
// }

// static int	ft_process_substrings(char **arr, char const *s, char c, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (*s && i < count)
// 	{
// 		if (*s != c && *s)
// 		{
// 			arr[i] = malloc((ft_len_subs(s, c) + 1) * sizeof(char));
// 			if (!arr[i])
// 			{
// 				while (i-- > 0)
// 					free(arr[i]);
// 				free(arr);
// 				return (0);
// 			}
// 			ft_strncpy(arr[i], s, ft_len_subs(s, c));
// 			arr[i][ft_len_subs(s, c)] = '\0';
// 			i++;
// 			s += ft_len_subs(s, c);
// 		}
// 		else
// 			s++;
// 	}
// 	return (1);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**arr;
// 	int		count;

// 	if (!s)
// 		return (NULL);
// 	count = ft_count_subs(s, c);
// 	arr = malloc((count + 1) * sizeof(char *));
// 	if (!arr)
// 		return (NULL);
// 	if (!ft_process_substrings(arr, s, c, count))
// 		return (NULL);
// 	arr[count] = NULL;
// 	return (arr);
// }
