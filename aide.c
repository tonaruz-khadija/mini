/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aide.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 06:16:28 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/13 22:39:41 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t l)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*t;

	i = 0;
	s = (unsigned char *)s1;
	t = (unsigned char *)s2;
	while (i < l && (s[i] != '\0' || t[i] != '\0'))
	{
		if (s[i] != t[i])
		{
			return (s[i] - t[i]);
		}
		i++;
	}
	return (0);
}

static char     *ft_strcat_strs(char *dest, char *src)
{
        int             i;
        int             j;
        char    *strs;

        i = 0;
        j = 0;
        strs = (char *)malloc((ft_strlen(dest) + ft_strlen(src) + 1));
        if (!strs)
        	return (NULL);
        while (dest && dest[i])
        {
        	strs[i] = dest[i];
        	i++;
        }
        while (src && src[j])
            strs[i++] = src[j++];
        strs[i] = '\0';
		free(dest);
		free(src);
        return (strs);
}

char    *ft_strjoina(const char *s1, const char *s2)
{
        char    *p1;
        char    *p2;

        if (!s1 && !s2)
                return (NULL);
        p1 = (char *)s1;
        p2 = (char *)s2;
        return (ft_strcat_strs(p1, p2));
}

int	ft_len_nb(long n)
{
	long	len;

	len = 0;
	if (n == 0)
	{
		len++;
	}
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)

{
	long long h;
	long long i;
	char *str;

	h = (long long)n;
	i = ft_len_nb(h);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (h == 0)
		str[0] = 48;
	if (h < 0)
	{
		str[0] = '-';
		h = -h;
	}
	i--;
	while (h > 0)
	{
		str[i] = (h % 10) + 48;
		h = h / 10;
		i--;
	}
	return (str);
}
