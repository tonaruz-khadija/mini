/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:37:31 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/05/25 10:45:57 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extr_pwd(t_exp *data)
{
	int		i;
	int		j;
	char	*ptr;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (data)
	{
		if (ft_strncmp(data->key, "PWD=", 3) == 0)
		{
			ptr = malloc(strlen(data->value) + 1);
			while (data->value[i])
			{
				ptr[i] = data->value[i];
				i++;
			}
			ptr[i] = '\0';
			printf("%s\n", ptr);
		}
		data = data->next;
	}
}

void	pwd_env(t_pars *pars, t_exp *data)
{
	int i = 0;
	while (pars)
	{
		i = 0;
		while (pars->cmds[i])
		{
			if (ft_strcmp(pars->cmds[i], "pwd") == 0)
			{
				extr_pwd(data);
			}
			i++;
		}
		pars = pars->next;
	}
}