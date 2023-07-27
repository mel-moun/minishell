/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:39:08 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/25 22:31:26 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	found_error_one(t_token **all)
{
	if (closed_double_quotes(g_glo.line) || !g_glo.expanded)
	{
		error_message(1, all);
		return (1);
	}
	if (g_glo.expanded[0] == '\0' || empty(g_glo.expanded))
	{
		error_message(0, all);
		return (1);
	}
	return (0);
}

int	found_error_two(t_token **all)
{
	if (syntax_error_first(all))
	{
		error_message(1, all);
		return (1);
	}
	return (0);
}

void	error_message(int err, t_token **all)
{
	if (err == 1)
	{
		printf("minishell: syntax error\n");
		g_glo.exitstatus = 1;
	}
	free(g_glo.line);
	g_glo.line = NULL;
	free(g_glo.expanded);
	g_glo.expanded = NULL;
	deallocating(all);
}
