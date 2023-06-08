/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quot_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:41:30 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/06 13:49:26 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quotes(char *s, int *j, char c)
{
	int		start;
	int		end;
	char	*str;

	start = 0;
	end = 0;
	if (c == '0')
	{
		start = *j;
		while (s[*j] && s[*j] != '\"' && s[*j] != '\'')
			(*j)++;
		end = *j;
		str = ft_substr(s, start, end - start);
		if (s[*j])
			(*j)--;
		return (str);
	}
	(*j)++;
	start = *j;
	while (s[*j] != c)
		(*j)++;
	end = (*j);
	str = ft_substr(s, start, end - start);
	return (str);
}

char	*min_skip(char *s, int *i, char c, char *str)
{
	char	*tmp;

	tmp = ft_strjoina(str, trim_quotes(s, i, c));
	str = tmp;
	return (str);
}

char	*skip_quot_exp(char *s)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = NULL;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'')
			str = min_skip(s, &i, '\'', str);
		else if (s[i] == '\"')
			str = min_skip(s, &i, '\"', str);
		else
		{
			tmp = ft_strjoina(str, trim_quotes(s, &i, '0'));
			str = tmp;
		}
		if (s[i])
			i++;
	}
	return (str);
}
