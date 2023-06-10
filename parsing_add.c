/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:37:59 by kelmouto          #+#    #+#             */
/*   Updated: 2023/05/13 21:04:07 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extr_path(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (env[i]);
		}
		i++;
	}
	return (0);
}

void	add_char(char **s, char c)
{
	char	*d;
	char	*m;
	int		i;

	i = 0;
	d = malloc(ft_strlen(*s) + 2);
	m = *s;
	while (*s && (*s)[i])
	{
		d[i] = (*s)[i];
		i++;
	}
	d[i] = c;
	d[i + 1] = 0;
	*s = d;
}
