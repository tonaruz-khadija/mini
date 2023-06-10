/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:45:16 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/09 15:27:15 by kelmouto         ###   ########.fr       */
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

void	should_add_sp(char *s, char **d, int i, int count)
{
	if ((!count || count % 2 == 0) && i && s[i - 1] != ' ' && s[i - 1] != s[i]
		&& (s[i] == '<' || s[i] == '>'))
	{
		add_char(d, ' ');
	}
	if ((!count || count % 2 == 0) && i && s[i - 1] != ' ' && s[i - 1] != s[i]
		&& (s[i] == '|' || s[i - 1] == '|'))
	{
		add_char(d, ' ');
	}
}

char	*add_sp(char *s)
{
	int		i;
	int		count;
	char	*d;

	d = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		should_add_sp(s, &d, i, count);
		if ((!count || count % 2 == 0) && (d && s[i - 1] != s[i]
				&& (d[ft_strlen(d) - 1] == '<' || d[ft_strlen(d) - 1] == '>'))
			&& s[i] != ' ')
			add_char(&d, ' ');
		if ((!count || count % 2 == 0) && (d && s[i - 1] != s[i]
				&& (d[ft_strlen(d) - 1] == '|' || d[ft_strlen(d) - 1] == '|'))
			&& s[i] != ' ')
			add_char(&d, ' ');
		else
			add_char(&d, s[i]);
		i++;
	}
	return (d);
}

void	check_symbole(t_pars *pars)
{
	int	i;

	i = 0;
	pars->cmd = add_sp(pars->cmd);
}

void	supprimer_espaces(char *s)
{
	int		len;
	bool	in_quotes;
	int		i;
	int		j;

	if (!s)
		return ;
	len = ft_strlen(s);
	in_quotes = false;
	i = 0;
	j = 0;
	while (i < len)
	{
		if (s[i] == '"' || s[i] == '\'')
			in_quotes = !in_quotes;
		if (in_quotes || (s[i] != ' ' || (i > 0 && s[i - 1] != ' ')) || (i == 0
				&& s[i] == ' '))
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}
