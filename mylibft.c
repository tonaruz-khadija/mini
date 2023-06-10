/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mylibft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 06:02:46 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/03 15:43:53 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *string, int r)
{
	char	*ptr;

	ptr = (char *)string;
	while (*ptr != (char)r && *ptr != '\0')
		ptr++;
	if (*ptr == (char)r)
		return (ptr);
	return (0);
}
char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	p = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 2);
	while (p && s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '/';
	i++;
	j = 0;
	while (p && s2 && s2[j])
		p[i++] = s2[j++];
	if (p)
		p[i] = 0;
	return (p);
}
char	*ft_strttcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)

{
	char *srrc;
	char *dest;
	int i;

	srrc = (char *)src;
	i = 0;
	dest = (char *)malloc(sizeof(char) * ft_strlen(srrc) + 1);
	if (!dest)
		return (NULL);
	return (ft_strttcpy(dest, srrc));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)

{
	unsigned int j;
	char *str;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else
	{
		if (len > ft_strlen(s))
			len = ft_strlen(s) - start;
		j = 0;
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!str)
			return (NULL);
		while (s[start] && j < len)
			str[j++] = s[start++];
		str[j] = '\0';
	}
	return (str);
}
