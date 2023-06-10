/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_normthree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:44:38 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/08 17:23:01 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cd_continue(t_exp *data, char *r, char *ptr)
{
	while (data)
	{
		if (strcmp((data->key), "PWD=") == 0)
			data->value = ptr;
		if (strcmp((data->key), "OLDPWD=") == 0)
			data->value = r;
		data = data->next;
	}
}

void	get_cd(t_exp *data)
{
	char	*ptr;
	char	*r;
	t_exp	*tmp;

	tmp = data;
	while (data)
	{
		if (strcmp(data->key, "PWD=") == 0)
		{
			r = malloc(strlen(data->value) + 1);
			r = data->value;
		}
		if (strcmp((data->key), "HOME=") == 0)
		{
			ptr = malloc(strlen(data->value) + 1);
			ptr = data->value;
		}
		data = data->next;
	}
	data = tmp;
	get_cd_continue(data, r, ptr);
}

void	mod_point(t_exp *data)
{
	char	*old;

	while (data)
	{
		if (strncmp((data->key), "PWD=", 4) == 0)
		{
			old = malloc(strlen(data->value) + 1);
			old = data->value;
			data->value = data->value;
		}
		if (strncmp((data->key), "OLDPWD=", 7) == 0)
		{
			data->value = old;
		}
		data = data->next;
	}
}

void	cd_deux_point(t_exp *data)
{
	if (chdir("..") == -1)
	{
		perror("chdir");
		return ;
	}
	while (data)
	{
		if (strcmp(data->key, "PWD=") == 0)
		{
			change_envir(data);
			if (strncmp(data->value, "/", strlen(data->value)) == 0)
			{
				data->value = ft_strjoin(data->value, " ");
			}
		}
		data = data->next;
	}
}
