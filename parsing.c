/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:33:17 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/08 13:24:32 by kelmouto         ###   ########.fr       */
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

char	**pr_envr(t_exp *data)
{
	int		i;
	t_exp	*tmp;
	int		e;
	char	**arr;

	arr = NULL;
	e = 0;
	i = 0;
	tmp = data;
	while (data)
	{
		e++;
		data = data->next;
	}
	arr = (char **)malloc((e + 1) * sizeof(char *));
	data = tmp;
	i = 0;
	while (data && i < e)
	{
		if(srch_egal(data->key))
		{
			arr[i] = ft_strjoina(data->key, data->value);
			i++;
		}
		data = data->next;
		
	}
	arr[i] = NULL;
	return (arr);
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


void	parsing(t_pars *pars, t_exp *data)
{
	char	**a;
	t_pars	*new_pars;
	char	**split;
	int		i;
	t_pars	*tmp;

	i = 0;
	(void)data;
	if (pars->cmd == NULL || pars->cmd[0] == '\0')
		return ;
	if (check_error(pars->cmd))
		return ;
	
	if (nmbr_quotes(pars->cmd) == 1)
	{
		printf("Syntax error : (close the quotes) \n");
		return ;
	}
	check_symbole(pars);
	a = my_split(pars->cmd, '|');
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
		tmp = pars;
	while (pars)
	{
		i = 0;
		while (pars->s[i])
		{
			if (strcmp(pars->s[i], "<<") == 0)
			{
				i++;
				if (pars->s[i][0] == '$')
				{
					i++;
				}
				if (pars->s[i] == NULL)
				{
					break ;
				}
			}
			if (pars->s[i][0] == '$')
			{
				pars->s[i] = expand(pars->s[i], data);
			}
			i++;
		}
		pars = pars->next;
	}
	pars = tmp;
	handl_redirec(pars, data);
	execution(pars, data);
}
