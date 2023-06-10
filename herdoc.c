/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:34:52 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/09 11:20:47 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	sig(int n)
{
	(void)n;
	write(1, "\n", 1);
	exit(1);
}
void	create_herdoc(t_pars *pars, char *str, t_exp *data)
{
	char	*ptr;
	int		i;
	int		k;
	int		status;

	k = 0;
	i = 0;
	signal(SIGINT, SIG_IGN);
	if (pipe(pars->herdoc_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	if (fork() == 0)
	{
		signal(SIGINT, sig);
		while (1)
		{
			ptr = readline("herdoc >");
			if (ptr == NULL)
				exit(0);
			if (strcmp(ptr, skip_quotes(str)) == 0)
			{
				free(ptr);
				break ;
			}
			if (ptr[k] == '$' && y_a_quotes(str) == 0 && str[0] != '$')
				ptr = ft_expand(ptr, data);
			write(pars->herdoc_fd[1], ptr, strlen(ptr));
			write(pars->herdoc_fd[1], "\n", 1);
			free(ptr);
		}
		exit(0);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			g_exit_status = WEXITSTATUS(status);
		}
		close(pars->herdoc_fd[1]);
	}
}
// plusieur herdoc ve signals.