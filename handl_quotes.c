/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:50:27 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/09 16:56:04 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nmbr_quotes(char *str)
{
	int	i;
	char c;

	i = 0;
	while(str[i])
	{
		if(str[i] == '"' || str[i] == '\'')
		{
			c =  str[i++];
			while(str[i] != c && str[i])
				i++;
			if(!str[i])
				return(1);
		}
		i++;
	}
	return (0);
}

int	y_a_quotes(char *str)
{
	int	i;

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
