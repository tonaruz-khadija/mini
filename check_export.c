/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:51:27 by kelmouto          #+#    #+#             */
/*   Updated: 2023/05/27 18:42:55 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	srch_egal(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*trim_egal(char *p)
{
	int		i;
	char	*v;

	i = 0;
	v = malloc(ft_strlen(p));
	while (p[i] && p[i] != '=')
	{
		v[i] = p[i];
		i++;
	}
	v[i] = '\0';
	return (v);
}

int	min_check(t_exp *new_tmp, char *s)
{
	char	*tmp;

	if (!ft_strcmp(new_tmp->key, s))
		return (1);
	else
	{
		tmp = ft_strjoina(new_tmp->key, "=");
		if (!ft_strcmp(tmp, s))
		{
			free(tmp);
			new_tmp->key = ft_strjoina(new_tmp->key, "=");
			return (1);
		}
	}
	return (0);
}

int	min_check2(t_exp *new_tmp, char *s)
{
	char	*t;

	t = trim_egal(new_tmp->key);
	if (!ft_strcmp(t, s))
	{
		free(t);
		return (1);
	}
	return (0);
}

int	check_export(t_exp **data, t_pars *pars, char *ptr)
{
	char	*s;
	t_exp	*new_tmp;

	new_tmp = (*data);
	s = get_key(pars, ptr);
	while (new_tmp)
	{
		if (srch_egal(new_tmp->key))
		{
			if (srch_egal(s))
			{
				if (!ft_strcmp(new_tmp->key, s))
					return (1);
			}
			else if (min_check2(new_tmp, s))
				return (1);
		}
		else if (min_check(new_tmp, s))
			return (1);
		new_tmp = new_tmp->next;
	}
	return (0);
}
