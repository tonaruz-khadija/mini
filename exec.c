/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:14:55 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/13 14:37:35 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_builtin(t_pars *pars, t_exp *data, int x)
{
	if (pars->cmds == NULL)
		return (1);
	if (pars->cmds && (strcmp(pars->cmds[0], "echo") == 0))
	{
		echo_exec(pars, data);
		return (1);
	}
	if (env_built(pars, data))
		return (1);
	if (cd_builtin(pars, data, x))
		return (1);
	if (pwd_unset(pars, data, x))
		return (1);
	if (exit_built(pars))
		return (1);
	if (export_built(pars, data))
		return (1);
	else
	{
		return (-1);
	}
}

void	func_multiple_pipe(t_pars *pars, t_exp *data)
{
	int		pid;
	int		i;
	char	**sp_path;
	char	*path;
	int		fd[2];
	char	*temp;
	int		j;
	int		x;
	char	**arr;
	int		status;

	x = 0;
	j = dup(0);
	i = 0;
	while (pars)
	{
		if (pars->next)
		{
			if (pipe(fd) == -1)
			{
				perror("Pipe failed");
				return ;
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("Fork failed");
			return ;
		}
		if (pid == 0)
		{
			path = ext_path(data);
			if (path == NULL)
			{
				printf("No such file or directory\n");
				return ;
			}
			sp_path = ft_split(path, ':');
			if (pars->next)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}
			if (check_if_builtin(pars, data, x) != 1)
			{
				if (pars->od > 0)
				{
					dup2(pars->od, 1);
					close(pars->od);
				}
				if (pars->od == -1)
				{
					exit(1);
				}
				if (pars->id == -1)
				{
					exit(1);
				}
				if (pars->id > 0)
				{
					dup2(pars->id, 0);
					close(pars->id);
				}
				if (pars->herdoc_fd[1] != -1)
				{
					dup2(pars->herdoc_fd[0], 0);
				}
				arr = pr_envr(data);
				if (access(pars->cmds[0], 0) == 0)
				{
					execve(pars->cmds[0], pars->cmds, arr);
				}
				if (pars->cmds[0] && !pars->cmds[1])
				{
					pars->cmds = ft_split(pars->cmds[0], ' ');
				}
				if (check_if_builtin(pars, data, x) != 1)
				{
					while (sp_path[i])
					{
						temp = ft_strjoin(sp_path[i], pars->cmds[0]);
						if (sp_path != NULL)
							free(sp_path[i]);
						sp_path[i] = temp;
						i++;
					}
					ft_access(sp_path, pars, data, arr);
				}
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
			else if (WIFSIGNALED(status))
			{
				g_exit_status = WTERMSIG(status) + 128;
			}
		}
		pars = pars->next;
		x++;
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	dup2(j, 0);
}

int	ft_lssize(t_pars *p)
{
	int	i;

	i = 0;
	if (p == NULL)
		return (0);
	while (p)
	{
		i++;
		p = p->next;
	}
	return (i);
}
void	execution(t_pars *pars, t_exp *data)
{
	int		pid;
	int		i;
	char	**sp_path;
	char	*path;
	int		fd[2];
	char	*temp;
	int		j;
	char	**arr;
	int		x;
	int		status;
	int		check_b;

	x = 0;
	j = dup(0);
	i = 0;
	if (ft_lssize(pars) == 1)
	{
		check_b = check_if_builtin(pars, data, x);
		if (check_b == -1)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("Fork failed");
				return ;
			}
			if (pid == 0)
			{
				path = ext_path(data);
				if (path == NULL)
				{
					printf("No such file or directory\n");
					return ;
				}
				sp_path = ft_splita(path, ':');
				if (pars->od == -1)
				{
					exit(1);
				}
				if (pars->od != -1 && pars->od > 0)
				{
					dup2(pars->od, 1);
					close(pars->od);
				}
				if (pars->id != -1)
				{
					dup2(pars->id, 0);
					close(pars->id);
				}
				if (pars->id == -1)
				{
					close(fd[1]);
					close(fd[0]);
					exit(1);
				}
				if (pars->herdoc_fd[1] == -2)
				{
					exit(1);
				}
				if (pars->herdoc_fd[1] != -1)
				{
					dup2(pars->herdoc_fd[0], 0);
				}
				arr = pr_envr(data);
				if (access(pars->cmds[0], 0) == 0)
				{
					execve(pars->cmds[0], pars->cmds, arr);
				}
				if (check_if_builtin(pars, data, x) != 1)
				{
					while (sp_path[i])
					{
						temp = ft_strjoin(sp_path[i], pars->cmds[0]);
						if (sp_path != NULL)
							free(sp_path[i]);
						sp_path[i] = temp;
						i++;
					}
					ft_access(sp_path, pars, data, arr);
				}
			}
		}
		else if (check_b == 1)
			return ;
		x++;
		wait(&status);
		if (WIFEXITED(status))
		{
			g_exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			g_exit_status = WTERMSIG(status) + 128;
		}
	}
	else
		func_multiple_pipe(pars, data);
}
