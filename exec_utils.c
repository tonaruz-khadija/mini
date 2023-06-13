/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:55:42 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/13 14:38:55 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_access(char **ptr, t_pars *pars, t_exp *data, char **arr)
{
	int	i;

	(void)data;
	i = 0;
	while (ptr[i])
	{
		
		if (access(ptr[i], 0) == 0)
		{
			
			return (execve(ptr[i], pars->cmds, arr));
		}
		i++;
	}
	ft_putstr_fd("Us~kel: ", 2);
	ft_putstr_fd(pars->cmds[0], 2);
	ft_putendl_fd(" :command not found", 2);
	exit(127);
}

char	*ext_path(t_exp *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data)
	{
		if (strcmp(data->key, "PATH=") == 0)
		{
			return (data->value);
		}
		data = data->next;
	}
	return (0);
}
