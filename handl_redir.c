/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:32:53 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/10 18:50:04 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_ambiguous(char *s)
{
	if(compter_mots(s,' ') > 1)
		return(-1);
	return(0);
}

void	ft_add_cmds(char *s, char ***cmds)
{
	char	**cmd;
	int		x;

	x = 0;
	while ((*cmds) && (*cmds)[x])
		x++;
	cmd = malloc(sizeof(char *) * (x + 2));
	x = 0;
	while (*cmds && (*cmds)[x])
	{
		cmd[x] = (*cmds)[x];
		x++;
	}
	cmd[x++] = s;
	cmd[x] = 0;
	*cmds = cmd;
}
void	handl_redirec(t_pars *pars, t_exp *data)
{
	int		i;
	t_pars	*pars_herdoc;

	pars_herdoc = NULL;
	pars->state = 0;
	while (pars)
	{
		pars->cmds = NULL;
		i = 0;
		while (pars->s && pars->s[i])
		{
			if (!strcmp(pars->s[i], ">"))
			{
				pars->s[i + 1] = skip_quot_exp(pars->s[i + 1]);
				pars->s[i + 1] = expand_file(pars->s[i + 1],data);
				if (check_ambiguous(pars->s[i + 1]))
				{
					printf("uskel : ambiguous redirect \n");
					g_exit_status = 1;
					pars->state = -4;
				}
				else
				{
					pars->od = open(pars->s[i + 1], O_CREAT | O_RDWR | O_TRUNC,
						0777);
					if(pars->od < 0)
					{
					perror("minishell : ");
					}
					i++;
				}
				
			}
			else if (!strcmp(pars->s[i], "<"))
			{
				pars->s[i + 1] = skip_quot_exp(pars->s[i + 1]);
				pars->s[i + 1] = expand_file(pars->s[i + 1],data);
				if (check_ambiguous(pars->s[i + 1]))
				{
					printf("uskel : ambiguous redirect \n");
					g_exit_status = 1;
					return ;
				}
				else
				{
					pars->id = open(pars->s[i + 1], O_RDWR, 0744);
					if (pars->id < 0)
					{
						perror("minishell : ");
						pars->state = -1;
					}
					i++;
				}
			}
			else if (strcmp(pars->s[i], "<<") == 0)
			{
				create_herdoc(pars, pars->s[i + 1], data);
				i++;
			}
			else if (!strcmp(pars->s[i], ">>"))
			{
				pars->s[i + 1] = skip_quot_exp(pars->s[i + 1]);
				pars->s[i + 1] = expand_file(pars->s[i + 1],data);
				if (check_ambiguous(pars->s[i + 1]))
				{
					printf("uskel : ambiguous redirect \n");
					g_exit_status = 1;
					return ;
				}
				else
				{
					pars->od = open(pars->s[i + 1], O_CREAT | O_RDWR | O_APPEND,
						0777);
					if(pars->od < 0)
					{
					perror("minishell : ");
					}
					i++;
				}
			}
			else
			{
				pars->s[i] = skip_quot_exp(pars->s[i]);
				ft_add_cmds(pars->s[i], &pars->cmds);
			}
			i++;
		}
		pars = pars->next;
	}
}
// int	check_file_conditions(t_exp *data, t_pars *pars, int s, int i)
// {
// 	if (strncmp(data->key, "PATH=", 5) == 0)
// 	{
// 		if (s == 0 && strcmp(pars->s[i + 1], data->value) == 0)
// 		{
// 			printf("minishell: %s : No such file or directory \n", pars->s[i
// 					+ 1]);
// 			return (1);
// 		}
// 	}
// 	else if (strncmp(data->key, "VSCODE_GIT_IPC_HANDLE=", 22) == 0
// 			|| strncmp(data->key, "SSH_AUTH_SOCK=", 14) == 0
// 			|| strncmp(data->key, "Apple_PubSub_Socket_Render=", 27) == 0)
// 	{
// 		if (s == 0 && strcmp(pars->s[i + 1], data->value) == 0)
// 		{
// 			printf("minishell : %s : Operation not supported on socket\n",
// 					pars->s[i + 1]);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// int	handle_output_redirect_conditions(t_exp *data, t_pars *pars, int s, int i)
// {
// 	if (strncmp(data->key, "TMPDIR=", 7) == 0 || strcmp(data->key,
// 			"ZDOTDIR=") == 0 || strcmp(data->key, "HOME=") == 0)
// 	{
// 		if (s == 0 && strcmp(pars->s[i + 1], data->value) == 0)
// 		{
// 			g_exit_status = 1;
// 			printf("minishell: %s Is a directory \n", pars->s[i + 1]);
// 			return (1);
// 		}
// 	}
// 	if (check_file_conditions(data, pars, s, i))
// 		return (1);
// 	return (0);
// }

// void	handle_output_redirect(t_pars *pars, t_exp *data, int i)
// {
// 	int	s;

// 	s = 0;
// 	pars->s[i + 1] = skip_quot_exp(pars->s[i + 1]);
// 	pars->s[i + 1] = expand_file(pars->s[i + 1],data);
// 	if (check_ambiguous(pars->s[i + 1]))
// 	{
// 		printf("uskel : ambiguous redirect \n");
// 		g_exit_status = 1;
// 		return ;
// 	}
// 	else
// 	{
// 		pars->od = open(pars->s[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
// 		if (pars->od < 0)
// 		{
// 			while (data)
// 			{
// 				if (handle_output_redirect_conditions(data, pars, s, i))
// 				{
// 					s++;
// 				}
// 				data = data->next;
// 			}
// 			if (s == 0)
// 			{
// 				g_exit_status = 1;
// 				perror("minishell : ");
// 			// print ambigous redirect
// 			}
// 		}
// 	}
// }

// void	handle_redirect_output(t_pars *pars, t_exp *data)
// {
// 	int	i;

// 	while (pars)
// 	{
// 		pars->cmds = NULL;
// 		i = 0;
// 		while (pars->s && pars->s[i])
// 		{
// 			if (!strcmp(pars->s[i], ">"))
// 			{
// 				handle_output_redirect(pars, data, i);
// 				i++;
// 			}
// 			else
// 			{
// 				ft_add_cmds(pars->s[i], &pars->cmds);
// 			}
// 			i++;
// 		}
// 		pars = pars->next;
// 	}
// }

// void	handle_input_redirect(t_pars *pars, int i)
// {
// 	pars->s[i + 1] = skip_quot_exp(pars->s[i + 1]);
// 	pars->id = open(pars->s[i + 1], O_RDWR, 0777);
// 	if (pars->id < 0)
// 	{
// 		g_exit_status = 1;
// 		perror("minishell : "); //chmod
// 	}
// }

