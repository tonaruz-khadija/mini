/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:58:44 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/10 17:00:23 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	old_var(t_exp *data)
{
	while (data)
	{
		if (strcmp(data->key, "OLDPWD=") == 0)
		{
			if (data->value)
				return (1);
		}
		data = data->next;
	}
	return (0);
}

void	ajout_oldpwd(t_exp *data, char *st)
{
	t_exp *tmp2;

	if (old_var(data) == 1)
		return ;

	tmp2 = data;
	while (data)
	{
		if (!ft_strcmp(data->key, "OLDPWD="))
		{
			data->value = st;
		}
		data = data->next;
	}
	data = tmp2;
}