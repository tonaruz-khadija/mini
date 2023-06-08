/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:15:29 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/08 14:16:20 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_built(t_pars *pars, t_exp *data)
{
	int	d;

	if (pars->cmds && ft_strcmp(pars->cmds[0], "echo") == 0)
	{
		if (pars->od != -1 && pars->od < 0)
		{
			ft_echo(pars->cmds, data);
			return (1);
		}
		else if (pars->od > 0)
		{
			d = dup(1);
			dup2(pars->od, 1);
			ft_echo(pars->cmds, data);
			dup2(d, 1);
			close(d);
			close(pars->od);
			return (1);
		}
		else if (pars->od == -1)
			return (1);
	}
	return (0);
}

int	cd_built(t_pars *pars, t_exp *data)
{
	t_exp	*dt;
	char	*st;

	if (pars->cmds[1] && ft_strcmp(pars->cmds[1], "-") != 0
		&& old_var(data) == 0)
	{
		dt = data;
		while (data)
		{
			if (strcmp(data->key, "PWD=") == 0)
			{
				st = malloc(strlen(data->value) + 1);
				st = strcpy(st, data->value);
			}
			data = data->next;
		}
		data = dt;
		if (cd_repa(pars, data) == 1)
		{
			ajout_oldpwd(data, st);
		}
		return (1);
	}
	return (0);
}

int	cd_builtin(t_pars *pars, t_exp *data, int x)
{
	if (pars->cmds && !ft_strcmp(pars->cmds[0], "cd"))
	{
		if (x == 0)
		{
			if (pars->cmds[1] && ft_strcmp(pars->cmds[1], "-") == 0
				&& old_var(data) == 0)
			{
				printf("minishell: cd: OLDPWD not set\n");
				return (1);
			}
			if (cd_built(pars, data))
				return (1);
			cd_repa(pars, data);
			return (1);
		}
		else
			exit(1);
	}
	return (0);
}
