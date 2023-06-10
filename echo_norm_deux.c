/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_norm_deux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:58:27 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/09 09:26:56 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	func_echo(char *cmds, char *cmdplus, t_exp *data)
{
	int	t;

	t = 0;
	if (t == 0 && (nmbr_qu(cmds) == 0 || nmbr_qu(cmds) == 2) && type_quot(cmds))
	{
		t++;
		cmds = skip_quotes(cmds);
		if (ft_expanda(cmds, data) != 0)
		{
			cmds = ft_expanda(cmds, data);
			write(1, cmds, ft_strlen(cmds));
			if (cmdplus)
				write(1, " ", 1);
		}
	}
	else if (
		type_quot(cmds) == 0 && t == 0)
	{
		t++;
		cmds = skip_single(cmds);
		write(1, cmds, ft_strlen(cmds));
		if (cmdplus)
			write(1, " ", 1);
	}
	return (t);
}

int	func_sans_n(char *cmds, t_exp *data)
{
	int	t;

	t = 0;
	if (t == 0 && (nmbr_qu(cmds) == 0 || nmbr_qu(cmds) == 2) && type_quot(cmds))
	{
		t++;
		cmds = skip_quotes(cmds);
		if (ft_expanda(cmds, data) != 0)
		{
			cmds = ft_expanda(cmds, data);
			printf("%s ", cmds);
		}
	}
	else if (
		type_quot(cmds) == 0 && t == 0)
	{
		t++;
		cmds = skip_single(cmds);
		printf("%s ", cmds);
	}
	return (t);
}
