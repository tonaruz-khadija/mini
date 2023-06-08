/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:51:33 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/05 20:16:25 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extr_envir(t_pars *pars, t_exp *data)
{
	int	i;

	i = 0;
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
