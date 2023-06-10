/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 06:00:44 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/05/13 20:55:50 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_wlen(char const *s, int c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

size_t	count_wrd(char const *s, int c, int i)
{
	size_t	len;

	len = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '"' && s[i] != '\'')
		{
			i++;
			len++;
		}
		return (len + 2);
	}
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

char	**ft_splita(char const *s, char c)
{
	int		i;
	int		start;
	char	**str;

	i = 0;
	start = -1;
	if (!s)
		return (0);
	str = (char **)malloc((ft_word(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (++start < ft_word(s, c))
	{
		while (s[i] == c)
			i++;
		str[start] = ft_substr(s, i, ft_wlen(s, c, i));
		if (str[start] == NULL)
		{
			ft_free(str);
			return (NULL);
		}
		i = i + ft_wlen(s, c, i);
	}
	str[start] = 0;
	return (str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (len);
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (len);
}
