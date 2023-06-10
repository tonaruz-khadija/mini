/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:08:22 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/10 16:37:06 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_back(t_exp **a, t_exp *new)
{
	t_exp	*t;

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

t_exp	*get_new_exp(t_pars *pars, char *ptr)
{
	char	*s;
	t_exp	*new_data;
	char	*v;

	s = get_key(pars, ptr);
	v = get_value(pars, ptr);
	new_data = malloc(sizeof(t_exp));
	if (v != NULL)
	{
		new_data->key = ft_strdup(s);
		free(s);
		new_data->value = ft_strdup(v);
		free(v);
	}
	else
	{
		new_data->key = ft_strdup(s);
		free(s);
		free(v);
	}
	new_data->next = NULL;
	return (new_data);
}

void	min_get_export(t_pars *pars, t_exp **data, char *ptr)
{
	t_exp	*new_data;

	new_data = get_new_exp(pars, ptr);
	ft_add_back(data, new_data);
}

void	min_get_exp(t_exp *tmp, t_pars *pars, char *ptr)
{
	char	*s;
	char	*v;

	s = get_key(pars, ptr);
	v = get_value(pars, ptr);
	if (!ft_strcmp(tmp->key, s))
	{
		if (srch_plus(ptr))
		{
			tmp->value = ft_strjoina(tmp->value, v);
			free(v);
		}
		else
			tmp->value = ft_strdup(v);
		return ;
	}
}

void	get_export(t_pars *pars, t_exp **data, char *p)
{
	t_exp	*tmp;

	if (p[0] == '=')
		perror_exp();
	if (err_exp(p))
		perror_exp();
	if (check_export(data, pars, p))
	{
		tmp = *data;
		while (tmp)
		{
			min_get_exp(tmp, pars, p);
			tmp = tmp->next;
		}
	}
	else
		min_get_export(pars, data, p);
}
