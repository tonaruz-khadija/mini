/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:50:22 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/13 21:27:01 by kelmouto         ###   ########.fr       */
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
		s = trim_egal(data->key);
		if (!ft_strcmp(s, p))
			return(free(s), data->value);
		else
			free(s);
		data = data->next;
	}
	return (NULL);
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