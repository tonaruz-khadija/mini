/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 06:07:56 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/13 23:11:05 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

// void	handl_c(int c)
// {
// 	(void)c;
// 	g_exit_status = 1;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

int	main(int ac, char **av, char **env)
{
	char *s;
	t_exp	*data;
	int		i;

	//signal(SIGINT, handl_c);
	(void)ac;
	(void)av;
	data = my_export(env);
	i = 0;
	while (1)
	{
		s = readline("Us~Kel> ");
		if (s && !s[0])
			continue ;
		if( !s)
			break;
		add_history(s);
		parsing(s, data);
		//system("leaks minishell");
	}
	return (0);
}
