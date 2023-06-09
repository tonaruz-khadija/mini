/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:35:13 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/13 21:55:00 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars *lstnew(char **s)
{
    t_pars *p;

    p = malloc(sizeof(t_pars));
    if(!p)
        exit(1);
    p->s = s;
    p->next = NULL;
	return(p);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	size_t	i;

	if (!s)
		return ;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	size_t	i;

	if (!s)
		return ;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
