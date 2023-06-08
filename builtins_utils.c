/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:27:46 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/08 14:15:21 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_builtins(t_pars *pars, t_exp *data)
{
	int	d;

	if (pars->state == -1)
		return (0);
	if (pars->od != -1 && pars->od < 0)
	{
		get_my_export(pars, data);
		return (1);
	}
	else if (pars->od > 0)
	{
		d = dup(1);
		dup2(pars->od, 1);
		get_my_export(pars, data);
		dup2(d, 1);
		close(d);
		close(pars->od);
		return (1);
	}
	else if (pars->od == -1)
		return (1);
	return (0);
}

int	export_built(t_pars *pars, t_exp *data)
{
	int	i;

	if (!ft_strcmp(pars->cmds[0], "export") && !pars->cmds[1])
	{
		if (exp_builtins(pars, data))
			return (1);
	}
	if (!ft_strcmp(pars->cmds[0], "export") && pars->cmds[1])
	{
		i = 1;
		while (pars->cmds[i])
		{
			get_export(pars, &data, pars->cmds[i]);
			i++;
		}
		if (pars->od > 0 || pars->id > 0)
			return (1);
		return (1);
	}
	return (0);
}

int	exit_built(t_pars *pars)
{
	if (pars->cmds && !ft_strcmp(pars->cmds[0], "exit"))
	{
		ft_exit(pars);
		return (1);
	}
	return (0);
}

int	pwd_unset(t_pars *pars, t_exp *data, int x)
{
	if (pars->cmds && ft_strcmp(pars->cmds[0], "pwd") == 0)
	{
		pwd_env(pars, data);
		return (1);
	}
	if (pars->cmds && !ft_strcmp(pars->cmds[0], "unset"))
	{
		if (x == 0)
		{
			unset_env(pars->cmds, data);
			return (1);
		}
		else
			exit(1);
	}
	return (0);
}

int	env_built(t_pars *pars, t_exp *data)
{
	if (pars->cmds && ft_strcmp(pars->cmds[0], "env") == 0)
	{
		extr_envir(pars, data);
		return (1);
	}
	return (0);
}
