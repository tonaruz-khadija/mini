/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:48:29 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/12 11:41:21 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_built(t_pars *pars, t_exp *data)
{
	char	*st;
	char	buffer[PATH_MAX];

	st = strdup(getcwd(buffer, sizeof(buffer)));
	if (pars->cmds[1] && ft_strcmp(pars->cmds[1], "-") != 0
		&& old_var(data) == 0)
	{
		if (cd_repa(pars, data) == 1)
		{
			ajout_oldpwd(data, st);
		}
		return (1);
	}
	else if (pars->cmds[1] == NULL)
	{
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
				g_exit_status = 1;
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
