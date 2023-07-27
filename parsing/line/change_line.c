/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:32:37 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/25 11:58:39 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*change_the_line(char *s)
{
	g_glo.i = 0;
	g_glo.str = NULL;
	g_glo.tmp = NULL;
	if (closed_double_quotes(s))
		return (NULL);
	while (s[g_glo.i])
	{
		handle_characters(s);
		if (s[g_glo.i] == '\'')
			handle_single_quotes(s);
		else if (s[g_glo.i] == '$')
			handle_dollar_signs(s);
		else if (s[g_glo.i] == '\"')
			handle_double_quotes(s);
		else if (s[g_glo.i] == '<')
			handle_heredoc(s);
		if (s[g_glo.i] == '\0')
			break ;
	}
	return (g_glo.str);
}

char	*change_heredoc(char *s)
{
	g_glo.i = 0;
	g_glo.str = NULL;
	g_glo.tmp = NULL;
	while (s[g_glo.i])
	{
		while (s[g_glo.i] && s[g_glo.i] != '$')
		{
			g_glo.str = mini_strjoin(g_glo.str, s[g_glo.i]);
			g_glo.i++;
		}
		if (s[g_glo.i] == '$')
		{
			handle_dollar_signs(s);
		}
		if (s[g_glo.i] == '\0')
			break ;
	}
	return (g_glo.str);
}
