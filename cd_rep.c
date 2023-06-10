/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_rep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:24:42 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/08 18:24:43 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mod_envr(t_exp *data, char *str)
{
	char	*old;
	int		i;

	i = 0;
	while (data)
	{
		if (strncmp((data->key), "PWD=", 4) == 0)
		{
			old = malloc(strlen(data->value) + 1);
			old = data->value;
			data->value = ft_strjoin(data->value, str);
		}
		if (strncmp((data->key), "OLDPWD=", 7) == 0)
		{
			data->value = old;
		}
		data = data->next;
	}
}

int	cd_continu(t_exp *data, char *str, int t)
{
	int	k;

	k = 0;
	if (t == 0 && str[k] == '$')
	{
		t++;
		cd_dollar(data, str);
		return (t);
	}
	else if (t == 0 && ft_strcmp(str, ".") == 0)
	{
		t++;
		cd_point(data);
		return (t);
	}
	else if (t == 0 && ft_strcmp(str, "..") == 0)
	{
		t++;
		cd_deux_point(data);
		return (t);
	}
	return (0);
}

int	cd_repa_iki(char *str, t_exp *data, int t)
{
	int	n;

	n = 0;
	if (t == 0 && str == NULL)
	{
		t++;
		sauf_cd(data);
	}
	else if (t == 0 && str[n] == '/' && str[n + 1] == '\0')
	{
		t++;
		if (chdir(str) == -1)
		{
			perror("chdir");
			return (0);
		}
		path_absolu(data, str);
		return (t);
	}
	t = cd_continu(data, str, t);
	return (t);
}

int	cd_repa_dort(char *str, t_exp *data, int t)
{
	if (t == 0 && str && ft_strcmp(str, "..") != 0 && ft_strcmp(str, ".") != 0)
	{
		t++;
		if (chdir(str) == -1)
		{
			perror("chdir");
			return (0);
		}
		mod_envr(data, str);
	}
	return (t);
}

int	cd_repa(t_pars *pars, t_exp *data)
{
	int	i;
	int	t;

	i = -1;
	t = 0;
	while (pars->cmds[++i])
	{
		if (ft_strcmp(pars->cmds[i], "cd") == 0)
		{
			t = cd_repa_iki(pars->cmds[i + 1], data, t);
			if (t == 0 && pars->cmds[i + 1] && ft_strcmp(pars->cmds[i + 1],
					"-") == 0)
			{
				t++;
				cd_dash(data);
			}
			t = cd_repa_dort(pars->cmds[i + 1], data, t);
			if (t == 0)
				return (0);
		}
	}
	return (1);
}
