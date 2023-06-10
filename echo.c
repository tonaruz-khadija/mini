/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:39:53 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/08 14:55:13 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*skip_double(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
			i++;
		else
		{
			i++;
			j++;
		}
	}
	result = malloc(j + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
			i++;
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	return (result);
}

char	*skip_single(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
			i++;
		else
		{
			i++;
			j++;
		}
	}
	result = malloc(j + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
			i++;
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	type_quot(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			return (1);
		if (str[i] == '\'')
			return (0);
		i++;
	}
	return (2);
}

int	var_quotes(char *str)
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

char	*skip_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		else
		{
			i++;
			j++;
		}
	}
	result = malloc(j + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	nmbr_qu(char *str)
{
	int	i;
	int	count;
	int	len;
	int	j;

	len = 0;
	count = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
		{
			count++;
		}
		else if (str[i] == '\'')
		{
			len++;
		}
		i++;
	}
	j = count + len;
	return (j);
}

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		if (str[i] == '\0')
			return (2);
	}
	return (1);
}

void	ft_echo(char **cmds, t_exp *data)
{
	int	i;
	int	t;
	int	a;

	a = 0;
	t = 0;
	i = 1;
	if (cmds[i] == NULL)
	{
		printf("\n");
		return ;
	}
	if (cmds[i] && check_n(cmds[i]) == 2)
	{
		echo_n(cmds, data, t, a);
	}
	else if (cmds[i] && strcmp(cmds[i], "-n") != 0)
	{
		echo_sans_n(cmds, data, t);
	}
}
