/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:03:58 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/09 13:53:17 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_atoi(char *v)
{
	int		i;
	long	nb;
	int		neg;
	char	*s;

	i = 0;
	nb = 0;
	neg = 1;
	s = skip_quotes(v);
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

int	check_nb(char *v)
{
	size_t	i;
	char	*s;

	i = 0;
	s = skip_quotes(v);
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

void	ft_exit(t_pars *pars)
{
	if (!pars->cmds[1])
	{
		printf("exit\n");
		exit(0);
	}
	else if (pars->cmds[1] && !pars->cmds[2])
	{
		if (check_nb(pars->cmds[1]))
		{
			printf("exit\n");
			exit(exit_atoi(pars->cmds[1]));
		}
		else
		{
			printf("exit\nuskel: exit: %s : numeric argument required\n",
					pars->cmds[1]);
			exit(255);
		}
	}
	else if (pars->cmds[1] && pars->cmds[2])
	{
		printf("exit\nuskel :exit: too many arguments\n");
	}
}
