/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:45:16 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/12 18:41:06 by ybouzafo         ###   ########.fr       */
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

void	squipe_toadd(char **at, char *s, char c, int *i)
{
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
	if (!ft_strcmp(s, "\"\""))
		return (s);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			squipe_toadd(&d, s, s[i], &i);
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
