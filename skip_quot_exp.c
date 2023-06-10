/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quot_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:41:30 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/09 18:36:53 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quotes(char *s, int *j, char c)
{
	int		start;
	int		end;
	char	*str;

	start = ++(*j);
	while (s[*j]&& s[*j] != c)
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

	i = 0;
	str = NULL;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] =='"')
			str = min_skip(s, &i, s[i], str);
		else
			add_char(&str, s[i]);
		i++;
	}
	return (str);
}
