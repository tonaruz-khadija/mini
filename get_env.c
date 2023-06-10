/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:01:35 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/09 14:03:22 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_pars *pars, char **env)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (env[count] != NULL)
	{
		count++;
	}
	pars->envr = (char **)malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		pars->envr[i] = env[i];
		i++;
	}
	pars->envr[count] = NULL;
	free(pars->envr);
}
