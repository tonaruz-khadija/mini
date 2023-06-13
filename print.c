/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:48:45 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/13 23:13:20 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	print(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		write(1, &line[i], 1);
		i++;
	}
}
void	print_noeud(t_pars *pars)
{
	int	i;

	while (pars)
	{
		i = 0;
		while (pars->cmds[i])
		{
			printf("--->%s\n", pars->cmds[i]);
			i++;
		}
		pars = pars->next;
	}
}
void	print_herdoc(t_pars *pars)
{
	while (pars)
	{
		printf("--->%s\n", pars->herdoc);
		pars = pars->next;
	}
}