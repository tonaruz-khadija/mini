/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_red_norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:20:40 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/13 10:54:06 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirect_input(t_pars *pars)
{
	int	i;

	while (pars)
	{
		pars->cmds = NULL;
		i = 0;
		while (pars->s && pars->s[i])
		{
			if (!strcmp(pars->s[i], "<"))
			{
				handle_input_redirect(pars, i);
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

void	handle_heredoc(t_pars *pars, t_exp *data, int i)
{
	pars->s[i + 1] = skip_quotes(pars->s[i + 1]);
	create_herdoc(pars, pars->s[i + 1], data);
}

void	handle_append_output_redirect(t_pars *pars, t_exp *data, int i)
{
	int	s;

	s = 0;
	pars->s[i + 1] = skip_quotes(pars->s[i + 1]);
	pars->s[i + 1] = expand_file(pars->s[i + 1], data);
	pars->od = open(pars->s[i + 1], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (pars->od < 0)
	{
		g_exit_status = 1;
		while (data)
		{
			if (pars->s[i + 1] == NULL)
			{
				s++;
				printf("us~kel : ambiguous redirect \n");
				break ;
			}
			if (handle_output_redirect_conditions(data, pars, s, i))
				s++;
			data = data->next;
		}
		if (s == 0)
			perror("us~kel : ");
	}
}

void	handl_redirec(t_pars *pars, t_exp *data)
{
	int	i;

	while (pars)
	{
		pars->cmds = NULL;
		i = 0;
		while (pars->s && pars->s[i])
		{
			if (!strcmp(pars->s[i], ">"))
			{
				handle_output_redirect(pars, data, i);
				i++;
			}
			else if (!strcmp(pars->s[i], "<"))
			{
				handle_input_redirect(pars, i);
				i++;
			}
			else if (strcmp(pars->s[i], "<<") == 0)
			{
				if (create_herdoc(pars, pars->s[i + 1], data) == 1)
				{
					pars->herdoc_fd[1] = -2;
					return ;
				}
				else
					i++;
			}
			else if (!strcmp(pars->s[i], ">>"))
			{
				handle_append_output_redirect(pars, data, i);
				i++;
			}
			else
			{
				if (ft_strcmp(pars->s[0], "\"\""))
					ft_add_cmds(skip_quot_exp(pars->s[i]), &pars->cmds);
				else
					ft_add_cmds(pars->s[i], &pars->cmds);
			}
			i++;
		}
		pars = pars->next;
	}
}
