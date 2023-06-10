/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:50:22 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/10 14:43:07 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_redir(char *p, int j)
{
	if (strnstr(p, ">", j))
		return (1);
	if (strnstr(p, "<", j))
		return (1);
	if (strnstr(p, ">>", j))
		return (1);
	if (strnstr(p, "<<", j))
		return (1);
	else
		return (0);
}
char	*expand_str(char *p, t_exp *data)
{
	t_exp	*tmp;
	char	*s;

	s = NULL;
	tmp = data;
	while (data)
	{
		if (!ft_strcmp(trim_egal(data->key), p))
		{
			if (data->value)
				s = ft_strdup(data->value);
			else
				s = NULL;
		}
		data = data->next;
	}
	return (s);
}

// char	*str_join1(char *v, char *f, char *p)
// {
// 	char	*str;

// 	str = NULL;
// 	str = ft_strjoina(p, "$");
// 	str = ft_strjoina(str, v);

// 	return (str);
// }
// char	*str_join2(char *p,char *t, char *f)
// {
// 	char	*str;

// 	str = NULL;
// 	str = ft_strjoina(p, t);
// 	return (str);
// }
// void	free_str(char *p, char *f, char *t, char *v)
// {
// 	// free(f);
// 	// free(p);
// 	// free(t);
// 	// free(v);
// }