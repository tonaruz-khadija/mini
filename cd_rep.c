/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_rep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:24:42 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/13 13:36:07 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	has_fonction(char *str, char *ptr, t_exp *data)
{
	char	buffer[PATH_MAX];
	char	*st;

	st = strdup(getcwd(buffer, sizeof(buffer)));
	while (data)
	{
		if (strcmp(data->key, ptr) == 0)
			data->value = str;
		if (strcmp(data->key, "PWD=") == 0)
			data->value = st;
		data = data->next;
	}
}
int	cd_repa(t_pars *pars, t_exp *data)
{
	int		i;
	char	buffer[PATH_MAX];
	char	*str;

	i = -1;
	while (pars->cmds[++i])
	{
		if (strcmp(pars->cmds[i], "cd") == 0)
		{
			str = strdup(getcwd(buffer, sizeof(buffer)));
			if (pars->s[i + 1] == NULL)
			{
				sauf_cd(data);
				return (1);
			}
			if (pars->s[i + 1] && strcmp(pars->s[i + 1], "-") != 0)
			{
				if (chdir(pars->cmds[i + 1]) == -1)
				{
					g_exit_status = 1;
					perror("chdir");
					return (0);
				}
				has_fonction(str, "OLDPWD=", data);
			}
			else
			{
				cd_dash(data);
				return (1);
			}
		}
	}
	return (1);
}
