/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:03:58 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/10 17:55:37 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *s)
{
	int			i;
	long		nb;
	int			neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (s[i] != '\0' && s[i] >= '0' && s[i] <= '9')
	{
		if (nb * 10 + (s[i] - '0') < nb && neg == 1)
			return (-1);
		if (nb * 10 + (s[i] - '0') < nb && neg == -1)
			return (0);
		nb = nb * 10 + (s[i++] - '0');
	}
	return (nb * neg);
}
int	exit_atoi(char *s)
{
	int		i;
	long	nb;
	int		neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i] == '+')
		i++;
	if (s[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (s[i] != '\0' && s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + (s[i++] - '0');
	}
	return (nb * neg);
}

int	check_nb(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		i++;
	if (i != ft_strlen(s))
		return (0);
	return (1);
}

int	cheek_max_min(char *s)
{
	int	tmp;

	tmp = ft_atoi(s);
	if ((tmp == -1 && ft_strncmp(s, "-1", 2)) || ((tmp == 0 && ft_strncmp(s,
					"0", 1) != 0) && (tmp == 0 && ft_strncmp(s, "-0", 2))
			&& (tmp == 0 && ft_strncmp(s, "+0", 2))))
		return (0);
	return (1);
}
void	ft_exit(t_pars *pars)
{
	if (!pars->cmds[1])
	{
		printf("exit\n");
		g_exit_status = 0;
		exit(g_exit_status);
	}
	else if (pars->cmds[1] && !pars->cmds[2])
	{
		if (check_nb(pars->cmds[1]))
		{
			if (!cheek_max_min(pars->cmds[1]))
			{
				printf("uskel: exit: numeric argument required \n");
				g_exit_status = 255;
				exit(g_exit_status);
			}
			else
			{
				printf("exit\n");
				g_exit_status = exit_atoi(pars->cmds[1]);
				exit(g_exit_status);
			}
		}
		else
		{
			printf("exit\nuskel: exit: %s : numeric argument required\n",
					pars->cmds[1]);
			g_exit_status = 255;
			exit(g_exit_status);
		}
	}
	else if (pars->cmds[1] && pars->cmds[2])
	{
		printf("exit\nuskel :exit: too many arguments\n");
		g_exit_status = 1;
	}
}
