/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:55:42 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/09 18:06:21 by kelmouto         ###   ########.fr       */
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
	write(2, "command not found\n", 18);
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
