/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:19:00 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/12 12:57:31 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compter_mots(char const *s, char c)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	n = 0;
	str = (char *)s;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != c && n == 0)
		{
			n = 1;
			i++;
		}
		else if (*str == c)
			n = 0;
		str++;
	}
	return (i);
}

void	func_free(char **s)
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

char	**fill_string(char const *s, char c, char **strings, int start)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (compter_mots(s, c) > j)
		{
			strings[j] = ft_substr(s, start, i - start);
			if (strings[j++] == NULL)
			{
				func_free(strings);
				return (NULL);
			}
		}
	}
	strings[j] = NULL;
	return (strings);
}

char	**ft_split(char *s, char c)
{
	int		i;
	char	**strings;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			squipe(s[i], s, &i);
		if (s[i] == c)
			s[i] = -1;
		i++;
	}
	c = -1;
	strings = (char **)malloc(sizeof(char *) * (compter_mots(s, c) + 1));
	if (!strings)
		return (NULL);
	return (fill_string(s, c, strings, 0));
}
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		i++;
	}
	return (i);
}
