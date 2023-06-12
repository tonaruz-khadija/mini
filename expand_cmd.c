/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:54:21 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/12 18:28:09 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pr_envr(t_exp *data)
{
	int		i;
	int		e;
	char	**arr;

	arr = NULL;
	e = 0;
	i = 0;
	arr = (char **)malloc((ft_ls_size(data) + 1) * sizeof(char *));
	i = 0;
	while (data && i < e)
	{
		if (srch_egal(data->key))
		{
			arr[i] = ft_strjoina(data->key, data->value);
			i++;
		}
		data = data->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	is_alph_num(char c)
{
	if ((c >= '0' && c <= '9') || ((c >= 'a' && c <= 'z')) || ((c >= 'A'
				&& c <= 'Z')) || (c == '_'))
		return (1);
	return (0);
}

int	ft_strcmp(char *p1, char *p2)
{
	int	i;

	i = 0;
	while ((p1[i] != '\0' || p2[i] != '\0'))
	{
		if (p1[i] != p2[i])
		{
			return (p1[i] - p2[i]);
		}
		i++;
	}
	return (0);
}

char	*expand_func(char *s, int *j, t_exp *data)
{
	char	*v;
	char	*t;
	int		start;

	start = ++(*j);
	if (s[*j] == '$')
		return (ft_strdup(""));
	if (s[*j] == '?')
	{
		return (ft_itoa(g_exit_status));
	}
	while (s[*j] && is_alph_num(s[*j]))
		(*j)++;
	v = ft_substr(s, start, *j - start);
	t = expand_str(v, data);
	(*j)--;
	return (t);
}

void	add_many_chars(char **s, char *st)
{
	int	i;

	i = 0;
	while (st && st[i])
	{
		add_char(s, st[i]);
		i++;
	}
}

void	squipe_pro(char *s, char **st, int *i, t_exp *data)
{
	char	c;

	c = s[*i];
	add_char(st, s[*i]);
	*i += 1;
	while (s[*i] != c)
	{
		if (s[*i] == '$' && c == '"')
			add_many_chars(st, expand_func(s, i, data));
		else
			add_char(st, s[*i]);
		*i += 1;
	}
	add_char(st, s[*i]);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	add_filename(char **s, char *a, int *i)
{
	char	c;

	c = a[*i];
	while (a[*i] == c)
		add_char(s, a[(*i)++]);
	while (ft_isspace(a[*i]))
		add_char(s, a[(*i)++]);
	while (!ft_isspace(a[*i]) && a[*i])
		add_char(s, a[(*i)++]);
	(*i)--;
}

char	**func_expand(char **a, t_exp *data)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (a[i])
	{
		j = 0;
		s = NULL;
		while (a[i][j])
		{
			if (a[i][j] == '<' || a[i][j] == '>')
				add_filename(&s, a[i], &j);
			else if (a[i][j] == '"' || a[i][j] == '\'')
				squipe_pro(a[i], &s, &j, data);
			else if (a[i][j] == '$')
				add_many_chars(&s, expand_func(a[i], &j, data));
			else
				add_char(&s, a[i][j]);
			j++;
		}
		a[i] = s;
		i++;
	}
	return (a);
}
