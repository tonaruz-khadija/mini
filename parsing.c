/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:33:17 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/13 23:18:49 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_to_pars(t_pars **a, t_pars *new)
{
	t_pars	*t;

	t = *a;
	if (!*a)
	{
		*a = new;
	}
	else
	{
		while (t->next)
			t = t->next;
		t->next = new;
	}
}

char	*expand_file(char *a, t_exp *data)
{
	char	*s;
	int		i;

	s = NULL;
	i = 0;
	while (a[i])
	{
		if (a[i] == '"' || a[i] == '\'')
			squipe_pro(a, &s, &i, data);
		else if (a[i] == '$')
			add_many_chars(&s, expand_func(a, &i, data));
		else
			add_char(&s, a[i]);
		i++;
	}
	if (compter_mots(s, ' ') > 1 || !s)
		return (free(a), NULL);
	return (free(a), s);
}

void	ft_freee(t_pars *pars)
{
	while(pars)
	{
		func_free(pars->s);
		pars = pars->next;
	}
}

void	parsing(char *s, t_exp *data)
{
	char	**a;
	t_pars	*pars;
	int		i;

	i = 0;
	if (nmbr_quotes(s) == 1)
	{
		printf("Syntax error : (close the quotes) \n");
		g_exit_status = 258;
		return ;
	}
	if (!check_error(s))
	{
		g_exit_status = 258;
		return ;
	}
	a = ft_split(add_sp(s), '|');
	a = func_expand(a, data);
	pars = NULL;
	while (a[i])
		ft_add_to_pars(&pars, lstnew(ft_split(a[i++], ' ')));
	free(a);
	handl_redirec(pars, data);
	execution(pars, data);
	ft_freee(pars);
}
