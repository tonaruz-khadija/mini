/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_norm_deux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:58:27 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/11 14:03:52 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	func_echo(char *cmds, char *cmdplus, t_exp *data)
{
	int	t;

	t = 0;
	(void)data;
	if (t == 0 && (nmbr_qu(cmds) == 0 || nmbr_qu(cmds) == 2) && type_quot(cmds))
	{
		t++;
		write(1, cmds, ft_strlen(cmds));
		if (cmdplus)
			write(1, " ", 1);
	}
	else if (
		type_quot(cmds) == 0 && t == 0)
	{
		t++;
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
	(void)data;
	if (t == 0 && (nmbr_qu(cmds) == 0 || nmbr_qu(cmds) == 2) && type_quot(cmds))
	{
		t++;
		printf("%s ", cmds);
	}
	else if (
		type_quot(cmds) == 0 && t == 0)
	{
		t++;
		printf("%s ", cmds);
	}
	return (t);
}
