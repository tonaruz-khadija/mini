/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:32:53 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/08 13:40:23 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				pars->od = open(pars->s[i + 1], O_CREAT | O_RDWR | O_TRUNC,
						0777);
				if (pars->od < 0)
				{
					while (data)
					{
						if (strncmp(data->key, "TMPDIR=", 7) == 0
							|| strcmp(data->key, "ZDOTDIR=") == 0
							|| strcmp(data->key, "HOME=") == 0)
						{
							if (strcmp(pars->s[i + 1], data->value) == 0)
							{
								printf("minishell: %s Is a directory \n",
										pars->s[i + 1]);
							}
						}
						if (strncmp(data->key, "PATH=", 5) == 0)
						{
							if (strcmp(pars->s[i + 1], data->value) == 0)
							{
								printf("minishell:"
										"%s : No such file  or  directory \n",
										pars->s[i + 1]);
							}
						}
						if (strncmp(data->key, "VSCODE_GIT_IPC_HANDLE=",
								22) == 0 || strncmp(data->key, "SSH_AUTH_SOCK=",
								14) == 0 || strncmp(data->key,
								"Apple_PubSub_Socket_Render=", 27) == 0)
						{
							if (strcmp(pars->s[i + 1], data->value) == 0)
							{
								printf("minishell : "
										"%s"
										": Operation not supported on socket\n",
										pars->s[i + 1]);
							}
						}
						data = data->next;
					}
					printf("minishell: ambiguous redirect \n");
				}
				i++;
			}
			else if (!strcmp(pars->s[i], "<"))
			{
				pars->s[i + 1] = skip_quot_exp(pars->s[i + 1]);
				pars->id = open(pars->s[i + 1], O_RDWR, 0744);
				// read only .
				if (pars->id < 0)
				{
					
					perror("minishell : ");
					pars->state = -1;
				}
				i++;
			}
			else if (strcmp(pars->s[i], "<<") == 0)
			{
				create_herdoc(pars, pars->s[i + 1], data);
				i++;
			}
			else if (!strcmp(pars->s[i], ">>"))
			{
				pars->s[i + 1] = skip_quot_exp(pars->s[i + 1]);
				pars->od = open(pars->s[i + 1], O_CREAT | O_RDWR | O_APPEND,
						0777);
				if (pars->od < 0)
				{
					while (data)
					{
						if (strncmp(data->key, "TMPDIR=", 7) == 0
							|| strcmp(data->key, "ZDOTDIR=") == 0
							|| strcmp(data->key, "HOME=") == 0)
						{
							if (strcmp(pars->s[i + 1], data->value) == 0)
							{
								printf("minishell: %s Is a directory \n",
										pars->s[i + 1]);
							}
						}
						if (strncmp(data->key, "PATH=", 5) == 0)
						{
							if (strcmp(pars->s[i + 1], data->value) == 0)
							{
								printf("minishell:"
										"%s : No such file  or  directory \n",
										pars->s[i + 1]);
							}
						}
						if (strncmp(data->key, "VSCODE_GIT_IPC_HANDLE=",
								22) == 0 || strncmp(data->key, "SSH_AUTH_SOCK=",
								14) == 0 || strncmp(data->key,
								"Apple_PubSub_Socket_Render=", 27) == 0)
						{
							if (strcmp(pars->s[i + 1], data->value) == 0)
							{
								printf("minishell : "
										"%s"
										": Operation not supported on socket\n",
										pars->s[i + 1]);
							}
						}
						data = data->next;
					}
					printf("minishell: ambiguous redirect \n");
				}
				i++;
			}
			else
			{
				ft_add_cmds(pars->s[i], &pars->cmds);
			}
			i++;
		}
		pars = pars->next;
	}
}
// void	handl_redirec(t_pars *pars, t_exp *data)
// {
// 	int		i;
// 	t_pars	*pars_herdoc;

// 	pars_herdoc = NULL;
// 	while (pars)
// 	{
// 		pars->cmds = NULL;
// 		i = 0;
// 		while (pars->s && pars->s[i])
// 		{
// 			if (!strcmp(pars->s[i], ">"))
// 			{
// 				pars->s[i + 1] = skip_quot_exp(pars->s[i + 1]);
// 				pars->od = open(pars->s[i + 1], O_CREAT | O_RDWR | O_TRUNC,
// 						0777);
// 				if (pars->od < 0)
// 				{
// 					while (data)
// 					{
// 						if (strncmp(data->key, "TMPDIR=", 7) == 0
// 							|| strcmp(data->key, "ZDOTDIR=") == 0
// 							|| strcmp(data->key, "HOME=") == 0)
// 						{
// 							if (strcmp(pars->s[i + 1], data->value) == 0)
// 							{
// 								printf("minishell: %s Is a directory \n",
// 										pars->s[i + 1]);
// 								return ;
// 							}
// 						}
// 						if (strncmp(data->key, "PATH=", 5) == 0)
// 						{
// 							if (strcmp(pars->s[i + 1], data->value) == 0)
// 							{
// 								printf("minishell:"
// 										"%s : No such file  or  directory \n",
// 										pars->s[i + 1]);
// 								return ;
// 							}
// 						}
// 						if (strncmp(data->key, "VSCODE_GIT_IPC_HANDLE=",
// 								22) == 0 || strncmp(data->key, "SSH_AUTH_SOCK=",
// 								14) == 0 || strncmp(data->key,
// 								"Apple_PubSub_Socket_Render=", 27) == 0)
// 						{
// 							if (strcmp(pars->s[i + 1], data->value) == 0)
// 							{
// 								printf("minishell : "
// 										"%s"
// 										": Operation not supported on socket\n",
// 										pars->s[i + 1]);
// 								return ;
// 							}
// 						}
// 						data = data->next;
// 					}
// 					printf("minishell: ambiguous redirect \n");
// 					//perror("minishell");
// 					return ;
// 				}
// 				i++;
// 			}
// 			else if (!strcmp(pars->s[i], "<"))
// 			{
// 				pars->s[i + 1] =skip_quot_exp(pars->s[i + 1]);
// 				pars->id = open(pars->s[i + 1], O_RDWR, 0744);
// 				if (pars->id < 0)
// 				{
// 					perror("minishell :");
				
// 				}
// 				i++;
// 			}
// 			else if (strcmp(pars->s[i], "<<") == 0)
// 			{
// 				create_herdoc(pars, pars->s[i + 1], data);
// 				i++;
// 			}
// 			else if (!strcmp(pars->s[i], ">>"))
// 			{
// 				pars->s[i + 1] = skip_quot_exp(pars->s[i + 1]);
// 				pars->od = open(pars->s[i + 1], O_CREAT | O_RDWR | O_APPEND,
// 						0777);
// 				if (pars->od < 0)
// 				{
// 					while (data)
// 					{
// 						if (strncmp(data->key, "TMPDIR=", 7) == 0
// 							|| strcmp(data->key, "ZDOTDIR=") == 0
// 							|| strcmp(data->key, "HOME=") == 0)
// 						{
// 							if (strcmp(pars->s[i + 1], data->value) == 0)
// 							{
// 								printf("minishell: %s Is a directory \n",
// 										pars->s[i + 1]);
							
// 							}
// 						}
// 						if (strncmp(data->key, "PATH=", 5) == 0)
// 						{
// 							if (strcmp(pars->s[i + 1], data->value) == 0)
// 							{
// 								printf("minishell:"
// 										"%s : No such file  or  directory \n",
// 										pars->s[i + 1]);
// 								return ;
// 							}
// 						}
// 						if (strncmp(data->key, "VSCODE_GIT_IPC_HANDLE=",
// 								22) == 0 || strncmp(data->key, "SSH_AUTH_SOCK=",
// 								14) == 0 || strncmp(data->key,
// 								"Apple_PubSub_Socket_Render=", 27) == 0)
// 						{
// 							if (strcmp(pars->s[i + 1], data->value) == 0)
// 							{
// 								printf("minishell : " "%s" ": Operation not supported on socket\n",pars->s[i + 1]);
// 								return ;
// 							}
// 						}
// 						data = data->next;
// 					}
// 					printf("minishell: ambiguous redirect \n");
// 					return ;
// 				}
// 				i++;
// 			}
// 			else
// 			{
// 				//printf("  s  : %s\n",pars->s[i]);
// 				ft_add_cmds(pars->s[i], &pars->cmds);
// 			}
// 			i++;
// 		}
// 		pars = pars->next;
// 	}
// }
