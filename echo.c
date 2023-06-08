/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:39:53 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/04 21:27:35 by kelmouto         ###   ########.fr       */
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
	int	j;
	int	k;
	int	x;

	j = 0;
	k = 0;
	x = 0;
	(void)data;
	i = 1;
	if (cmds[i] == NULL)
	{
		printf("\n");
		return ;
	}
	if (cmds[i] && check_n(cmds[i]) == 2)
	{
		i = 2;
		while (cmds[i] && check_n(cmds[i]) == 2)
			i++;
		while (cmds[i])
		{
			if ((nmbr_qu(cmds[i]) == 0 || nmbr_qu(cmds[i]) == 2)
				&& type_quot(cmds[i]))
			{
				cmds[i] = skip_quotes(cmds[i]);
				if (ft_expanda(cmds[i], data) == 0)
				{
					write(1, cmds[i], ft_strlen(cmds[i]));
					if (cmds[i + 1])
						write(1, " ", 1);
				}
			}
			else if (
				type_quot(cmds[i]) == 0)
			{
				cmds[i] = skip_single(cmds[i]);
				write(1, cmds[i], ft_strlen(cmds[i]));
				if (cmds[i + 1])
					write(1, " ", 1);
			}
			else if (nmbr_qu(cmds[i]) != 2 && type_quot(cmds[i]) != 0)
			{
				cmds[i] = skip_double(cmds[i]);
				write(1, cmds[i], ft_strlen(cmds[i]));
				if (cmds[i + 1])
					write(1, " ", 1);
			}
			else
			{
				cmds[i] = skip_quotes(cmds[i]);
				write(1, cmds[i], ft_strlen(cmds[i]));
				if (cmds[i + 1])
					write(1, " ", 1);
			}
			i++;
		}
	}
	else if (cmds[i] && strcmp(cmds[i], "-n") != 0)
	{
		while (cmds && cmds[i])
		{
			if ((nmbr_qu(cmds[i]) == 0 || nmbr_qu(cmds[i]) == 2)
				&& type_quot(cmds[i]))
			{
				cmds[i] = skip_quotes(cmds[i]);
				if (ft_expanda(cmds[i], data) == 0)
				{
					printf("%s ", cmds[i]);
				}
			}
			else if (
				type_quot(cmds[i]) == 0)
			{
				cmds[i] = skip_single(cmds[i]);
				printf("%s ", cmds[i]);
			}
			else if (nmbr_qu(cmds[i]) != 2 && type_quot(cmds[i]) != 0)
			{
				cmds[i] = skip_double(cmds[i]);
				printf("%s ", cmds[i]);
			}
			else
			{
				cmds[i] = skip_quotes(cmds[i]);
				printf("%s ", cmds[i]);
			}
			i++;
		}
		printf("\n");
	}
}
