/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:24:21 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/12 11:46:15 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_exec(t_pars *pars, t_exp *data)
{
	int	d;

	if (pars->od != -1 && pars->od < 0)
	{
		g_exit_status = 0;
		ft_echo(pars->cmds, data);
		return (1);
	}
	else if (pars->od > 0)
	{
		g_exit_status = 0;
		d = dup(1);
		dup2(pars->od, 1);
		ft_echo(pars->cmds, data);
		dup2(d, 1);
		close(d);
		close(pars->od);
		return (1);
	}
	else if (pars->od == -1)
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	echo_sans_n(char **cmds, t_exp *data, int t)
{
	int	i;

	t = 0;
	i = 1;
	while (cmds && cmds[i])
	{
		t = func_sans_n(cmds[i], data);
		if (t == 0 && nmbr_qu(cmds[i]) != 2 && type_quot(cmds[i]) != 0)
		{
			t++;
			cmds[i] = skip_double(cmds[i]);
			printf("%s ", cmds[i]);
		}
		else if (t == 0)
		{
			cmds[i] = skip_quotes(cmds[i]);
			printf("%s ", cmds[i]);
		}
		i++;
	}
	printf("\n");
}

void	echo_n(char **cmds, t_exp *data, int t, int i)
{
	t = 0;
	i = 2;
	while (cmds[i] && check_n(cmds[i]) == 2)
		i++;
	while (cmds[i])
	{
		t = func_echo(cmds[i], cmds[i + 1], data);
		if (t == 0 && nmbr_qu(cmds[i]) != 2 && type_quot(cmds[i]) != 0)
		{
			write(1, cmds[i], ft_strlen(cmds[i]));
			if (cmds[i + 1])
				write(1, " ", 1);
		}
		else if (t == 0)
		{
			write(1, cmds[i], ft_strlen(cmds[i]));
			if (cmds[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
}
