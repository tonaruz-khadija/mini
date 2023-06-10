/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_my_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:08:09 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/09 14:04:16 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_my_export(t_pars *pars, t_exp *data)
{
	(void)pars;
	while (data)
	{
		printf("declare -x ");
		if (srch_egal(data->key))
		{
			if (data->value)
			{
				printf("%s", data->key);
				printf("\"");
				printf("%s", data->value);
				printf("\"\n");
			}
			else
			{
				printf("%s\n", trim_egal(data->key));
			}
		}
		else
			printf("%s\n", data->key);
		data = data->next;
	}
}
