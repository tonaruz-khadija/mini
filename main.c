/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 06:07:56 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/06 14:12:31 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

// void	handl_c(int c)
// {
// 	(void)c;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

int	main(int ac, char **av, char **env)
{
	t_pars	*pars;
	t_exp	*data;
	int		i;

	//signal(SIGINT, handl_c);
	pars = malloc(sizeof(t_pars));
	(void)ac;
	(void)av;
	
	data = my_export(env);
	// pars->cmd = NULL;
	i = 0;
	while (1)
	{
		// free(pars->cmd);
		pars->cmd = readline("Us~Kel> ");
		//printf("---->%s\n", pars->cmd);
		if (pars->cmd && !pars->cmd[0])
			continue ;
		if (pars->cmd == NULL)
			exit(1);
		add_history(pars->cmd);
		parsing(pars, data);
	}
	printf("\n");
	return (0);
}
