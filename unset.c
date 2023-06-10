/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:07:21 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/09 14:07:31 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_enva(t_exp *data, char *var_name)
{
	t_exp	*current;
	t_exp	*previous;
	int		i;

	i = 0;
	current = data;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var_name) == 0)
		{
			if (previous == NULL)
				data = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	unset_env(char **cmds, t_exp *data)
{
	int		i;
	char	*var_name;

	i = 1;
	while (cmds[i])
	{
		var_name = malloc(ft_strlen(cmds[i]) + 2);
		var_name = ft_strjoina(cmds[i], "=");
		unset_enva(data, var_name);
		i++;
	}
}
