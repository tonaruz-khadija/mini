/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:33:17 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/12 14:18:16 by ybouzafo         ###   ########.fr       */
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
	if (compter_mots(s, ' ') > 1)
	{
		printf("uskel : ambiguous redirect \n");
		return (NULL);
	}
	return (s);
}

void	parsing(t_pars *pars, t_exp *data)
{
	char	**a;
	t_pars	*new_pars;
	char	**split;
	int		i;
	int		t;

	t = 0;
	i = 0;
	if (pars->cmd == NULL || pars->cmd[0] == '\0')
		return ;
	if (nmbr_quotes(pars->cmd) == 1)
	{
		printf("Syntax error : (close the quotes) \n");
		g_exit_status = 258;
		return ;
	}
	if (!check_error(pars->cmd))
	{
		g_exit_status = 258;
		return ;
	}
	check_symbole(pars);
	a = ft_split(pars->cmd, '|');
	a = func_expand(a, data);
	pars = NULL;
	while (*a)
	{
		new_pars = malloc(sizeof(t_pars));
		if (!new_pars)
			exit(1);
		new_pars->next = NULL;
		split = ft_split(*a, ' ');
		new_pars->s = split;
		ft_add_to_pars(&pars, new_pars);
		a++;
	}
	handl_redirec(pars, data);
	execution(pars, data);
}
