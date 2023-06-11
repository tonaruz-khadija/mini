/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:54:23 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/11 18:30:01 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_perror(void)
{
	printf("Syntax error\n");
	return (-1);
}

// int	check_double_redirec2(char *str)
// {
// 	if (str[0] == '>' && str[1] == '>' && !str[2])
// 		return (ft_perror());
// 	return (0);
// }

// int	check_double_redirec1(char *str)
// {
// 	if (str[0] == '<' && str[1] == '<' && !str[2])
// 		return (ft_perror());
// 	return (0);
// }

// int	check_last_char(char *str)
// {
// 	int	len;

// 	len = ft_strlen(str);
// 	if (str[len - 1] == '|')
// 		return (ft_perror());
// 	if (str && str[len - 1] == ' ')
// 	{
// 		if (str && str[len - 2] == '|' && str[len - 1] == ' ')
// 			return (ft_perror());
// 		while (str[len - 1] == ' ')
// 		{
// 			len--;
// 			if (len == 0 || (len == 1 && str[0] == '|') || (len > 1 && str[len
// 					- 2] == '|' && str[len - 1] == ' '))
// 				return (ft_perror());
// 			if (str[len - 1] == '|')
// 				return (ft_perror());
// 		}
// 	}
// 	return (0);
// }

// int	check_pipe(char *str, int i)
// {
// 	if (str[i] == '|' && str[i + 1] == '|')
// 		return (ft_perror());
// 	if (str[i] == '|')
// 	{
// 		i++;
// 		while (str[i] == ' ')
// 			i++;
// 		if (!is_alphanum(str[i]))
// 			return (ft_perror());
// 	}
// 	return (i);
// }

// int	check_redirect(char *str, int i)
// {
	
// 	if (((str[i] == '>' && str[i + 1] != '>') || (str[i] == '<' && str[i
// 				+ 1] != '<')))
// 	{
// 		i++;
// 		while (str[i] == ' ')
// 			i++;
// 		if (!is_alphanum(str[i]))
// 			return (ft_perror());
// 	}
// 	return (i);
// }

// int	check_justspace(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
// 		i++;
// 	if (i == ft_strlen(str))
// 		return (-1);
// 	return (0);
// }

void squipe(char c, char *s, int *i)
{
	*i += 1;
	while(s[*i] != c)
		*i += 1;
}

// int	check_ozel_char(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str && (str[i] == ' ' || str[i] == '\t'))
// 		i++;
// 	while (str[i])
// 	{
// 		if(str[i] == '\'' || str[i] == '"')
// 			squipe(str[i], str, &i);
// 		if (str[i] == '<' && str[i + 1] == '>')
// 			return (ft_perror());
// 		if (str[i] == '>' && str[i + 1] == '<')
// 			return (ft_perror());
// 		if ((i = check_pipe(str, i)) == -1)
// 			return (-1);
// 		if ((i = check_redirect(str, i)) == -1)
// 			return (-1);
// 		if (str[i] == '*' || str[i] == ';')
// 			return (ft_perror());
// 		i++;
// 	}
// 	return (0);
// }

// int	check_error(char *str)
// {
// 	if (check_justspace(str))
// 		return (-1);
// 	if (check_double_redirec2(str) == -1)
// 		return (-1);
// 	if (check_double_redirec1(str) == -1)
// 		return (-1);
// 	if (check_last_char(str) == -1)
// 		return (-1);
// 	if (check_ozel_char(str) == -1)
// 		return (-1);
// 	return (0);
// }
// int	check_error(char *s)
// {
// 	int i = 0;
	
// }