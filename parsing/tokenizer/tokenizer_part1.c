/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_part1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:42:44 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/22 16:22:37 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parsing_part_one(t_token **all, char *expanded)
{
	creating_linked(all, expanded);
	delete_empty_nodes(all);
	if (!all || !*all)
	{
		free(g_glo.expanded);
		free(g_glo.line);
		g_glo.expanded = NULL;
		g_glo.line = NULL;
		deallocating(all);
		return (1);
	}
	if (all && *all)
		setup_exact_type(all);
	return (0);
}

void	creating_linked(t_token **all, char *s)
{
	initialization_of_vars();
	while (s[g_glo.i])
	{
		if (s[g_glo.i] != 32 && s[g_glo.i] != '\t' \
		&& s[g_glo.i] != '<' && s[g_glo.i] != '>' \
		&& s[g_glo.i] != '|' && s[g_glo.i] != 1 \
		&& s[g_glo.i] != '\0')
			take_the_whole_node(s, all);
		if (s[g_glo.i] == 1)
			take_arg_heredoc(s, all);
		else if (s[g_glo.i] == '|')
			take_pipe(all);
		else if (s[g_glo.i] == '>')
			take_append(s, all);
		else if (s[g_glo.i] == '<')
			take_heredoc(all, s);
		else if (s[g_glo.i++] == '\0')
			break ;
	}
}
