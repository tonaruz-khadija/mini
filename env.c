/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:51:33 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/12 11:47:21 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ls_size(t_exp *p)
{
	int	i;

	i = 0;
	if (p == NULL)
		return (0);
	while (p)
	{
		i++;
		p = p->next;
	}
	return (i);
}

void	extr_envir(t_pars *pars, t_exp *data)
{
	int	i;

	i = 0;
	g_exit_status = 0;
	while (pars)
	{
		i = 0;
		while (pars->cmds[i])
		{
			if (!ft_strcmp(pars->cmds[i], "env"))
			{
				while (data)
				{
					if (srch_egal(data->key) && data->value != NULL)
					{
						printf("%s", data->key);
						printf("%s\n", data->value);
					}
					data = data->next;
				}
			}
			i++;
		}
		pars = pars->next;
	}
}
