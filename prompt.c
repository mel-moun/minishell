/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:28:30 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/26 16:28:54 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(void)
{
	signal(SIGINT, handler_fnct);
	signal(SIGQUIT, SIG_IGN);
}

int	prompt(t_token **all, t_all **glo, char **envp)
{
	handle_signals();
	g_glo.exitstatus = 0;
	while (1)
	{
		g_glo.line = readline("minishell> ");
		if (g_glo.line == NULL)
		{
			printf("exit\n");
			return (g_glo.exitstatus);
		}
		if (g_glo.line[0] != '\0')
		{
			add_history(g_glo.line);
			g_glo.expanded = change_the_line(g_glo.line);
			if (found_error_one(all) || !g_glo.expanded)
				continue ;
			if (parsing_part_one(all, g_glo.expanded) || found_error_two(all))
				continue ;
			parsing_part_two(all, glo);
			execution_fnct(*glo, envp);
			clear_all(glo);
		}
		error_message(0, all);
	}
	return (g_glo.exitstatus);
}
