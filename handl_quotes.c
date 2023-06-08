/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:50:27 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/05/31 08:16:10 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nmbr_quotes(char *str)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			count++;
		}
		if (str[i] == '\'')
		{
			check++;
		}
		i++;
	}
	if (count % 2 != 0 || check % 2 != 0)
	{
		return (1);
	}
	return (0);
}

int	y_a_quotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			return (1);
		}
		i++;
	}
	return (0);
}