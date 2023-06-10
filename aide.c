/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aide.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 06:16:28 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/09 13:50:14 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t l)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*t;

	i = 0;
	s = (unsigned char *)s1;
	t = (unsigned char *)s2;
	while (i < l && (s[i] != '\0' || t[i] != '\0'))
	{
		if (s[i] != t[i])
		{
			return (s[i] - t[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strjoina(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	p = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 2);
	while (p && s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (p && s2 && s2[j])
		p[i++] = s2[j++];
	if (p)
		p[i] = 0;
	return (p);
}
