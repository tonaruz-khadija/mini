/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_normfor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 08:41:15 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/08 18:05:38 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sauf_cd(t_exp *data)
{
	while (data)
	{
		if (strcmp((data->key), "HOME=") == 0)
		{
			if (chdir(data->value) == -1)
			{
				perror("chdir");
				return ;
			}
			if (chdir(data->value) == 0)
			{
				get_cd(data);
			}
		}
		data = data->next;
	}
}

void	add_old(t_exp *data, char *ptr)
{
	char	*str;

	while (data)
	{
		if (ft_strcmp(data->key, "PWD=") == 0)
		{
			str = malloc(strlen(data->value) + 1);
			str = data->value;
			data->value = ptr;
		}
		if (ft_strcmp(data->key, "OLDPWD=") == 0)
		{
			data->value = str;
		}
		data = data->next;
	}
}

void	cd_dash(t_exp *data)
{
	char	*ptr;
	t_exp	*tmp;

	tmp = data;
	while (data)
	{
		if (strcmp((data->key), "OLDPWD=") == 0)
		{
			ptr = malloc(strlen(data->value) + 1);
			ptr = data->value;
			printf("%s\n", data->value);
			chdir(data->value);
		}
		data = data->next;
	}
	data = tmp;
	add_old(data, ptr);
}

void	cd_dollar(t_exp *data, char *str)
{
	char	*ex;

	ex = ft_expand(str, data);
	change_pwd(ex, data);
	if (chdir(ex) == -1)
	{
		perror("chdir");
		return ;
	}
}

void	cd_point(t_exp *data)
{
	if (chdir(".") == 0)
	{
		mod_point(data);
	}
	else
	{
		perror("chdir");
		return ;
	}
}
