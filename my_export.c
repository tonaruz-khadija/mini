/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:29:37 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/06 14:24:39 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_value(char *s, int k)
{
	int		j;
	char	*p;

	j = 0;
	p = malloc(ft_strlen(s) - k);
	k++;
	while (s[k])
	{
		p[j] = s[k];
		k++;
		j++;
	}
	p[j] = '\0';
	return (p);
}

char	*copy_key(char *s, int k)
{
	int		j;
	char	*p;

	p = malloc(k + 2);
	j = 0;
	while (s[j] && s[j] != '=')
	{
		p[j] = s[j];
		j++;
	}
	p[j] = '=';
	p[++j] = '\0';
	return (p);
}

t_exp	*init(t_exp *data)
{
	data = malloc(sizeof(t_exp));
	data->next = NULL;
	return (data);
}

t_exp	*my_export(char **env)
{
	int		i;
	int		k;
	t_exp	*data;
	t_exp	*new_data;

	data = NULL;
	new_data = NULL;
	i = 0;
	check_pwd_env(env, data, new_data);
	while (env[i])
	{
		k = 0;
		data = init(data);
		if (env && env[i][k] != '=')
		{
			while (env[i][k] && env[i][k] != '=')
				k++;
			data->key = copy_key(env[i], k);
		}
		if (env[i][k] == '=')
			srch_oldpwd(data, env[i], k);
		ft_add_back(&new_data, data);
		i++;
	}
	return (new_data);
}
