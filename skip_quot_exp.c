/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quot_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:41:30 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/12 11:34:53 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quotes(char *s, int *j, char c)
{
	int		start;
	int		end;
	char	*str;

	start = ++(*j);
	while (s[*j] && s[*j] != c)
		(*j)++;
	end = (*j);
	str = ft_substr(s, start, end - start);
	// printf("str : %s\n",str);
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
		if (s[i] == '\'')
			str = min_skip(s, &i, s[i], str);
		if (s[i] == '"')
			str = min_skip(s, &i, s[i], str);
		else
			add_char(&str, s[i]);
		if (s[i])
			i++;
	}
	return (str);
}
