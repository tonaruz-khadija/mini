/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:18:22 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/13 23:03:18 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_env_null(t_exp *data, t_exp *new, t_exp *current, t_exp *tmp)
{
	char	buff[1024];

	data->key = ft_strdup("PWD=");
	data->value = getcwd(buff, sizeof(buff));
	new->key = ft_strdup("SHLVL=");
	new->value = ft_strdup("1");
	current->key = ft_strdup("_=");
	current->value = ft_strdup("/usr/bin/env");
	tmp->key = ft_strdup("OLDPWD=");
	tmp->value = NULL;
}

t_exp	*env_null(t_exp *new_data, t_exp *data)
{
	t_exp	*current;
	t_exp	*new;
	t_exp	*tmp;

	data = malloc(sizeof(t_exp));
	data->next = NULL;
	current = malloc(sizeof(t_exp));
	current->next = NULL;
	new = malloc(sizeof(t_exp));
	new->next = NULL;
	tmp = malloc(sizeof(t_exp));
	tmp->next = NULL;
	min_env_null(data, new, current, tmp);
	ft_add_back(&new_data, data);
	ft_add_back(&new_data, new);
	ft_add_back(&new_data, current);
	ft_add_back(&new_data, tmp);
	return (new_data);
}

void	srch_oldpwd(t_exp *data, char *s, int k)
{
	if (ft_strcmp(data->key, "OLDPWD=") == 0)
		data->value = 0;
	else
		data->value = copy_value(s, k);
}

void	check_pwd_env(char **env, t_exp *data, t_exp *new_data)
{
	if (!env[0])
		new_data = env_null(new_data, data);
}
