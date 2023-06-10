/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:48:29 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/09 13:49:47 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
