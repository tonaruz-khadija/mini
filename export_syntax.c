/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:39:10 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/10 17:16:52 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alph_digit(char c)
{
	if (((c >= 'a' && c <= 'z')) || ((c >= 'A'
				&& c <= 'Z')) || (c == '\'') || (c == '"'))
		return (1);
	return (0);
}

int	check_er_syntax(char *s)
{
	int	i;

	i = 0;
	if (srch_plus(s))
	{
		while (s[i] && s[i] != '+')
		{
			if (!is_alph_digit(s[i]))
				return (-1);
			i++;
		}
	}
	else
	{
		while (s[i] && s[i] != '=')
		{
			if (!is_alph_digit(s[i]))
				return (-1);
			i++;
		}
	}
	return (0);
}

int	err_exp(char *s)
{
	int	i;

	i = 0;
	if (srch_egal(s))
	{
		if (check_er_syntax(s))
			return (-1);
	}
	else
	{
		while (s[i])
		{
			if (!is_alph_digit(s[i]))
				return (-1);
			i++;
		}
	}
	return (0);
}

void	perror_exp(void)
{
	printf("minishell: export: `syntax': not a valid identifier\n");
	g_exit_status = 1;
	return ;
}
