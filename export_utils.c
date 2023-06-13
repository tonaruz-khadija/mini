/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:44:19 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/13 20:38:48 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	srch_plus(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*min_key(char *s, int k)
{
	char	*p;
	int		j;

	j = 0;
	p = malloc(k + 2);
	while (j < k)
	{
		p[j] = s[j];
		if (p[j] == '+')
			j++;
		j++;
	}
	p[j] = '=';
	p[++j] = '\0';
	return (p);
}

char	*get_key(t_pars *pars, char *s)
{
	int		k;
	char	*p;

	(void)pars;
	k = 0;
	if (srch_egal(s))
	{
		while (s[k] && s[k] != '=')
			k++;
		if (s[k - 1] == '+')
			k--;
		p = min_key(s, k);
	}
	else
		p = ft_strdup(s);
	return (p);
}

char	*min_value(char *s, char *p)
{
	char	*v;
	int		k;
	int		j;

	k = 0;
	j = 0;
	v = malloc(ft_strlen(s) - ft_strlen(p) + 1);
	while (s[k] && s[k] != '=')
		k++;
	if (s[k] == '=')
	{
		k++;
		while (s[k] != '\0')
		{
			v[j] = s[k];
			k++;
			j++;
		}
		v[j] = '\0';
	}
	return (v);
}

char	*get_value(t_pars *pars, char *s)
{
	int		k;
	int		j;
	char	*v;
	char	*p;

	k = 0;
	j = 0;
	p = get_key(pars, s);
	if (srch_egal(s))
		v = min_value(s, p);
	else
		v = NULL;
	free(p);
	return (v);
}
