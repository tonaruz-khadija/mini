/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_rep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:24:42 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/08 20:14:06 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	mod_envr(t_exp *data, char *str)
{
	char	*old;
	int		i;

	i = 0;
	while (data)
	{
		if (strncmp((data->key), "PWD=", 4) == 0)
		{
			old = malloc(strlen(data->value) + 1);
			old = data->value;
			data->value = ft_strjoin(data->value, str);
		}
		if (strncmp((data->key), "OLDPWD=", 7) == 0)
		{
			data->value = old;
		}
		data = data->next;
	}
}

int	cd_continu(t_exp *data, char *str, int t)
{
	int	k;

	k = 0;
	if (t == 0 && str[k] == '$')
	{
		t++;
		cd_dollar(data, str);
		return (t);
	}
	else if (t == 0 && ft_strcmp(str, ".") == 0)
	{
		t++;
		cd_point(data);
		return (t);
	}
	else if (t == 0 && ft_strcmp(str, "..") == 0)
	{
		t++;
		cd_deux_point(data);
		return (t);
	}
	return (0);
}

int	cd_repa_iki(char *str, t_exp *data, int t)
{
	int	n;

	n = 0;
	if (t == 0 && str == NULL)
	{
		t++;
		sauf_cd(data);
	}
	else if (t == 0 && str[n] == '/' && str[n + 1] == '\0')
	{
		t++;
		if (chdir(str) == -1)
		{
			perror("chdir");
			return (0);
		}
		path_absolu(data, str);
		return (t);
	}
	t = cd_continu(data, str, t);
	return (t);
}

int	cd_repa_dort(char *str, t_exp *data, int t)
{
	if (t == 0 && str && ft_strcmp(str, "..") != 0 && ft_strcmp(str, ".") != 0)
	{
		t++;
		if (chdir(str) == -1)
		{
			perror("chdir");
			return (0);
		}
		mod_envr(data, str);
	}
	return (t);
}

int	cd_repa(t_pars *pars, t_exp *data)
{
	int	i;
	int	t;

	i = -1;
	t = 0;
	while (pars->cmds[++i])
	{
		if (ft_strcmp(pars->cmds[i], "cd") == 0)
		{
			t = cd_repa_iki(pars->cmds[i + 1], data, t);
			if (t == 0 && pars->cmds[i + 1] && ft_strcmp(pars->cmds[i + 1],
					"-") == 0)
			{
				t++;
				cd_dash(data);
			}
			t = cd_repa_dort(pars->cmds[i + 1], data, t);
			if (t == 0)
				return (0);
		}
	}
	return (1);
}






































// void	mod_envr(t_exp *data, char *str)
// {
// 	char	*old;
// 	int		i;

// 	i = 0;
// 	while (data)
// 	{
// 		if (strncmp((data->key), "PWD=", 4) == 0)
// 		{
// 			old = malloc(strlen(data->value) + 1);
// 			old = data->value;
// 			data->value = ft_strjoin(data->value, str);
// 		}
// 		if (strncmp((data->key), "OLDPWD=", 7) == 0)
// 		{
// 			data->value = old;
// 		}
// 		data = data->next;
// 	}
// }
// void	path_absolu(t_exp *data, char *str)
// {
// 	char	*old;

// 	while (data)
// 	{
// 		if (strncmp((data->key), "PWD=", 4) == 0)
// 		{
// 			old = malloc(strlen(data->value) + 1);
// 			old = data->value;
// 			data->value = str;
// 		}
// 		if (strncmp((data->key), "OLDPWD=", 7) == 0)
// 		{
// 			data->value = old;
// 		}
// 		data = data->next;
// 	}
// }
// void	mod_point(t_exp *data)
// {
// 	char	*old;

// 	while (data)
// 	{
// 		if (strncmp((data->key), "PWD=", 4) == 0)
// 		{
// 			old = malloc(strlen(data->value) + 1);
// 			old = data->value;
// 			data->value = data->value;
// 		}
// 		if (strncmp((data->key), "OLDPWD=", 7) == 0)
// 		{
// 			data->value = old;
// 		}
// 		data = data->next;
// 	}
// }

// void	change_envir(t_exp *data)
// {
// 	int		len;
// 	int		i;
// 	int		j;
// 	char	*str;
// 	char	*old;

// 	j = 0;
// 	i = 0;
// 	while (data)
// 	{
// 		if (strncmp((data->key), "PWD=", 4) == 0)
// 		{
// 			old = malloc(strlen(data->value) + 1);
// 			old = data->value;
// 			len = ft_strlen(data->value);
// 			while (data->value[len] != '/')
// 			{
// 				len--;
// 			}
// 			str = malloc(len + 1);
// 			while (i < len)
// 			{
// 				str[i] = data->value[i];
// 				i++;
// 			}
// 			str[i] = '\0';
// 			data->value = str;
// 		}
// 		if (strncmp((data->key), "OLDPWD=", 7) == 0)
// 		{
// 			data->value = old;
// 		}
// 		data = data->next;
// 	}
// }
// void	get_cd(t_exp *data)
// {
// 	t_exp	*temp;
// 	char	*ptr;
// 	char	*r;

// 	temp = data;
// 	while (data)
// 	{
// 		if (strcmp(data->key, "PWD=") == 0)
// 		{
// 			r = malloc(strlen(data->value) + 1);
// 			r = data->value;
// 		}
// 		if (strcmp((data->key), "HOME=") == 0)
// 		{
// 			ptr = malloc(strlen(data->value) + 1);
// 			ptr = data->value;
// 		}
// 		data = data->next;
// 	}
// 	data = temp;
// 	while (data)
// 	{
// 		if (strcmp((data->key), "PWD=") == 0)
// 		{
// 			data->value = ptr;
// 		}
// 		if (strcmp((data->key), "OLDPWD=") == 0)
// 		{
// 			data->value = r;
// 		}
// 		data = data->next;
// 	}
// }

// void	change_pwd(char *str, t_exp *data)
// {
// 	char	*ex;
// 	char	*mal;
// 	t_exp	*temp;
// 	char	*ah;

// 	ex = ft_expand(str, data);
// 	temp = data;
// 	while (data)
// 	{
// 		if (strcmp(data->value, ex) == 0)
// 		{
// 			mal = malloc(strlen(data->value) + 1);
// 			mal = data->value;
// 		}
// 		data = data->next;
// 	}
// 	data = temp;
// 	while (data)
// 	{
// 		if (strcmp(data->key, "PWD=") == 0)
// 		{
// 			ah = malloc(strlen(data->value) + 1);
// 			ah = data->value;
// 			data->value = mal;
// 		}
// 		else if (strcmp(data->key, "OLDPWD=") == 0)
// 		{
// 			data->value = ah;
// 		}
// 		data = data->next;
// 	}
// }

// int	cd_repa(t_pars *pars, t_exp *data)
// {
// 	int		i;
// 	int		j;
// 	t_exp	*temp;
// 	char	*str;
// 	int		k;
// 	char	*ex;
// 	int		n;
// 	char	*ptr;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	n = 0;
// 	while (pars->cmds[i])
// 	{
// 		if (ft_strcmp(pars->cmds[i], "cd") == 0)
// 		{
// 			if (pars->cmds[i + 1])
// 			{
// 				pars->cmds[i + 1] = skip_quotes(pars->cmds[i + 1]);
// 			}
// 			if (pars->cmds[i + 1] == NULL)
// 			{
// 				while (data)
// 				{
// 					if (strcmp((data->key), "HOME=") == 0)
// 					{
// 						if (chdir(data->value) == -1)
// 						{
// 							perror("chdir");
// 							return (0);
// 						}
// 						if (chdir(data->value) == 0)
// 						{
// 							get_cd(data);
// 						}
// 					}
// 					data = data->next;
// 				}
// 			}
// 			else if (pars->cmds[i + 1][n] == '/')
// 			{
// 				if (chdir(pars->cmds[i + 1]) == -1)
// 				{
// 					perror("chdir");
// 					return (0);
// 				}
// 				path_absolu(data, pars->cmds[i + 1]);
// 			}
// 			else if (pars->cmds[i + 1][k] == '$')
// 			{
// 				ex = ft_expand(pars->cmds[i + 1], data);
// 				change_pwd(pars->cmds[i + 1], data);
// 				if (chdir(ex) == -1)
// 				{
// 					perror("chdir");
// 					return (0);
// 				}
// 			}
// 			else if (ft_strcmp(pars->cmds[i + 1], "-") == 0)
// 			{
// 				temp = data;
// 				while (data)
// 				{
// 					if (strcmp((data->key), "OLDPWD=") == 0)
// 					{
// 						ptr = malloc(strlen(data->value) + 1);
// 						ptr = data->value;
// 						printf("%s\n", data->value);
// 						// if (chdir == -1)
// 						// {
// 						// 	perror("chdir");
// 						// 	return (0);
// 						// }
// 					}
// 					data = data->next;
// 				}
// 				data = temp;
// 				while (data)
// 				{
// 					if (ft_strcmp(data->key, "PWD=") == 0)
// 					{
// 						str = malloc(strlen(data->value) + 1);
// 						str = data->value;
// 						data->value = ptr;
// 					}
// 					if (ft_strcmp(data->key, "OLDPWD=") == 0)
// 					{
// 						data->value = str;
// 					}
// 					data = data->next;
// 				}
// 			}
// 			else if (ft_strcmp(pars->cmds[i + 1], ".") == 0)
// 			{
// 				if (chdir(".") == 0)
// 				{
// 					mod_point(data);
// 				}
// 				else
// 				{
// 					perror("chdir");
// 					return (0);
// 				}
// 			}
// 			else if (ft_strcmp(pars->cmds[i + 1], "..") == 0)
// 			{
// 				if (chdir("..") == -1)
// 				{
// 					perror("chdir");
// 					return (0);
// 				}
// 				while (data)
// 				{
// 					if (strcmp(data->key, "PWD=") == 0)
// 					{
// 						change_envir(data);
// 						if (strncmp(data->value, "/", strlen(data->value)) == 0)
// 						{
// 							data->value = ft_strjoin(data->value, " ");
// 						}
// 					}
// 					data = data->next;
// 				}
// 			}
// 			else if (ft_strcmp(pars->cmds[i + 1], "..") != 0
// 					&& ft_strcmp(pars->cmds[i + 1], ".") != 0)
// 			{
// 				if (chdir(pars->cmds[i + 1]) == -1)
// 				{
// 					perror("chdir");
// 					return (0);
// 				}
// 				mod_envr(data, pars->cmds[i + 1]);
// 			}
// 		}
// 		i++;
// 	}
// 	return (1);
// }