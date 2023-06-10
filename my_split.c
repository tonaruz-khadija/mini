/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:19:00 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/09 18:23:05 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_word(char const *str, char d)
{
	int	i;
	int	mo;
	int	len;

	i = 0;
	mo = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] != d)
		{
			while (str[i] != d && i < len)
			{
				if (str[i] == '"' || str[i] == '\'')
				{
					while (str[i] != '"' && str[i] != '\'')
						i++;
					break ;
				}
				i++;
			}
			mo++;
		}
		i++;
	}
	return (mo);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		start;
	int		in_quotes;
	char	**str;
	int		k;

	i = 0;
	j = 0;
	start = -1;
	in_quotes = 0;
	if (!s)
		return (0);
	str = (char **)malloc((ft_word(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (++start < ft_word(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		str[start] = (char *)malloc(ft_strlen(s) + 1);
		if (!str[start])
		{
			k = 0;
			while (k < start)
			{
				free(str[k]);
				k++;
			}
			free(str);
			return (NULL);
		}
		while (s[i] != '\0' && (s[i] != c || in_quotes))
		{
			if ((s[i] == '\"' || s[i] == '\'') && !in_quotes)
			{
				in_quotes = 1;
				str[start][j++] = s[i++];
				continue ;
			}
			if ((s[i] == '\"' || s[i] == '\'') && in_quotes)
			{
				in_quotes = 0;
				str[start][j++] = s[i++];
				continue ;
			}
			str[start][j++] = s[i++];
		}
		str[start][j] = '\0';
		j = 0;
	}
	str[start] = 0;
	return (str);
}

char	**my_split(char *s, char c)
{
	char	**save;
	char	*str;
	int		in_quotes;
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(s);
	save = malloc((len + 1) * sizeof(char *));
	str = malloc((len + 1) * sizeof(char));
	save[0] = NULL;
	in_quotes = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			in_quotes = !in_quotes;
		}
		if (!in_quotes && s[i] == c)
		{
			str[k] = '\0';
			save[j++] = strdup(str);
			k = 0;
			str[0] = '\0';
			i++;
		}
		else
		{
			str[k++] = s[i++];
		}
	}
	if (k > 0)
	{
		str[k] = '\0';
		save[j++] = strdup(str);
	}
	save[j] = NULL;
	free(str);
	return (save);
}
