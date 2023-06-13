/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_normfor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 08:41:15 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/13 13:20:28 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	get_cd(char *old, char *pwd, t_exp *data)
{
	while (data)
	{
		if (strcmp((data->key), "PWD=") == 0)
		{
			data->value = pwd;
		}
		if (strcmp((data->key), "OLDPWD=") == 0)
		{
			data->value = old;
		}
		data = data->next;
	}
}
void	sauf_cd(t_exp *data)
{
	char	*old;
	char	buffer[PATH_MAX];
	char	*pwd;

	old = strdup(getcwd(buffer, sizeof(buffer)));
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
				pwd = malloc(strlen(data->value) + 1);
				pwd = data->value;
				get_cd(old, pwd, data);
			}
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
			if (chdir(data->value) == -1)
			{
				g_exit_status = 1;
				perror("chdir");
				return ;
			}
		}
		data = data->next;
	}
	data = tmp;
	add_old(data, ptr);
}
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
void	add_old(t_exp *data, char *ptr)
{
	char *str;

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