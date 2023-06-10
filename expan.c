/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:43:14 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/10 09:51:06 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_env(char *str)
{
	int		i;
	int		j;
	char	*doll;
	int		t;

	t = 0;
	doll = NULL;
	j = 0;
	i = 0;
	
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			doll = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
			if (doll == NULL)
				return (0);
			while (str[i])
				doll[j++] = str[i++];
			doll[j] = '\0';
			break ;
		}
		i++;
	}
	return (doll);
}

char	*egal_egal(t_exp *data, char *comp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(comp) + 2);
	while (comp[i])
	{
		str[i] = comp[i];
		i++;
	}
	str[i] = '=';
	i++;
	str[i] = '\0';
	while (comp && data)
	{
		if (strcmp(str, data->key) == 0)
			return (data->value);
		data = data->next;
	}
	return (0);
}

char	*egal(t_exp *data, char *comp)
{
	int		i;
	int		j;
	char	*str;
	t_exp	*temp;

	i = -1;
	j = 0;
	str = malloc(ft_strlen(comp) + 2);
	while (comp[++i])
		str[i] = comp[i];
	str[i] = '=';
	str[i++] = '\0';
	temp = data;
	while (comp && data)
	{
		if (strcmp(str, data->key) == 0)
			return (data->value);
		data = data->next;
	}
	data = temp;
	while (data)
	{
		if (strcmp(data->key, "HOME=") == 0)
			return (data->value);
		data = data->next;
	}
	printf("\n");
	return (0);
}

char	*ft_expand(char *str, t_exp *data)
{
	int		i;
	char	*compare_dol;
	char	*bha;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			compare_dol = check_env(str);
			bha = egal(data, compare_dol);
			return (bha);
		}
		i++;
	}
	return (str);
}

// char	*expand(char *str, t_exp *data)
// {
// 	int		i;
// 	char	*compare_dol;
// 	char	*bha;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			compare_dol = check_env(str);
// 			bha = egal_egal(data, compare_dol);
// 			return (bha);
// 		}
// 		i++;
// 	}
// 	return (str);
// }


char	*expand(char *str, t_exp *data)
{
	int		i;
	char	*compare_dol;
	char	*bha;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			printf("yyyyeh\n");
			compare_dol = check_env(str);
			bha = egal_egal(data, compare_dol);
			return (bha);
		}
		i++;
	}
	return (str);
}
char	*ft_expanda(char *str, t_exp *data)
{
	int		i;
	char	*compare_dol;
	char	*bha;

	compare_dol = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '\0')
		{
			return (0);
		}
		if (str[i] == '$')
		{
			compare_dol = check_env(str);
			bha = egal_egal(data, compare_dol);
			if (bha == NULL)
				return (0);
			return (bha);
		}
		i++;
	}
	return (str);
}
