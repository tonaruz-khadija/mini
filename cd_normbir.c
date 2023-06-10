/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_normbir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:02:17 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/08 18:06:32 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_absolu(t_exp *data, char *str)
{
	char	*old;

	while (data)
	{
		if (strncmp((data->key), "PWD=", 4) == 0)
		{
			old = malloc(strlen(data->value) + 1);
			old = data->value;
			data->value = str;
		}
		if (strncmp((data->key), "OLDPWD=", 7) == 0)
		{
			data->value = old;
		}
		data = data->next;
	}
}

void	change_envir(t_exp *data)
{
	int		len;
	int		i;
	char	*str;
	char	*old;

	i = -1;
	while (data)
	{
		if (strncmp((data->key), "PWD=", 4) == 0)
		{
			old = malloc(strlen(data->value) + 1);
			old = data->value;
			len = ft_strlen(data->value);
			while (data->value[len] != '/')
				len--;
			str = malloc(len + 1);
			while (++i < len)
				str[i] = data->value[i];
			str[i] = '\0';
			data->value = str;
		}
		if (strncmp((data->key), "OLDPWD=", 7) == 0)
			data->value = old;
		data = data->next;
	}
}

void	change_pwd_continue(t_exp *data, char *mal)
{
	char	*ah;

	while (data)
	{
		if (strcmp(data->key, "PWD=") == 0)
		{
			ah = malloc(strlen(data->value) + 1);
			ah = data->value;
			data->value = mal;
		}
		else if (strcmp(data->key, "OLDPWD=") == 0)
		{
			data->value = ah;
		}
		data = data->next;
	}
}

void	change_pwd(char *str, t_exp *data)
{
	char	*mal;
	t_exp	*tmp;

	tmp = data;
	mal = NULL;
	while (data)
	{
		if (ft_strcmp(data->value, str) == 0)
		{
			mal = malloc(strlen(data->value) + 1);
			mal = data->value;
			break ;
		}
		data = data->next;
	}
	data = tmp;
	change_pwd_continue(data, mal);
}
