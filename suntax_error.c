/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:54:23 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/12 18:06:16 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	squipe(char c, char *s, int *i)
{
	*i += 1;
	while (s[*i] && s[*i] != c)
		*i += 1;
}

int	check_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			squipe(s[i], s, &i);
		else if (s[i] == '|')
		{
			i++;
			while (ft_isspace(s[i]))
				i++;
			if (s[i] == '|')
			{
				printf("uskel: syntax error near unexpected token `|'\n");
				g_exit_status = 258;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	is_all_space(char *s)
{
	int	len;

	len = ft_strlen(s) - 1;
	while (ft_isspace(s[len]))
		len--;
	if (s[len] == '>' || s[len] == '<' || s[len] == '|')
	{
		g_exit_status = 258;
		printf("uskel : syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	ft_perror(void)
{
	g_exit_status = 258;
	printf("uskel :syntax error near ");
	printf("unexpected token  \n");
	return (0);
}

int	check_error(char *s)
{
	int		i;
	char	c;

	i = 0;
	if (!is_all_space(s))
		return (0);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			squipe(s[i], s, &i);
		else if (s[i] == '>' || s[i] == '<')
		{
			c = s[i++];
			(s[i] == c) && (i++);
			while (ft_isspace(s[i]))
				i++;
			if (s[i] == '>' || s[i] == '<' || s[i] == '|')
				return (ft_perror());
		}
		else if (s[i] == ';' || s[i] == '*' || s[i] == ',')
			return (ft_perror());
		i++;
	}
	return (check_pipe(s));
}
