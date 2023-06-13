/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:45:16 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/13 23:12:47 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alphanum(char c)
{
	if ((c >= '0' && c <= '9') || ((c >= 'a' && c <= 'z')) || ((c >= 'A'
				&& c <= 'Z')) || (c == '\'') || (c == '"') || (c == '$'))
		return (1);
	return (0);
}

void	squipe_toadd(char **at, char *s, char c, int *i)
{
	if ((*at) && ((*at)[ft_strlen((*at)) - 1] == '>' || (*at)[ft_strlen((*at)) - 1] == '<') && s[*i] != (*at)[ft_strlen((*at)) - 1] && s[*i] != ' ')
		add_char(at, ' ');
	add_char(at, s[(*i)++]);
	while (s[*i] != c)
		add_char(at, s[(*i)++]);
	add_char(at, s[(*i)++]);
}

char	*add_sp(char *s)
{
	int		i;
	int		count;
	char	*d;

	d = 0;
	i = 0;
	count = 0;
	// if (!ft_strcmp(s, "\"\"") || !ft_strcmp(s, "\"\\\""))
	// 	return (s);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			squipe_toadd(&d, s, s[i], &i);
		if ((s[i] == '<' || s[i] == '>') && d && d[ft_strlen(d) - 1] != s[i] && d[ft_strlen(d) - 1] != ' ')
			add_char(&d, ' ');
		else if (d && (d[ft_strlen(d) - 1] == '>' || d[ft_strlen(d) - 1] == '<') && s[i] != d[ft_strlen(d) - 1] && s[i] != ' ')
			add_char(&d, ' ');
		add_char(&d, s[i++]);
	}
	return (free(s), d);
}

