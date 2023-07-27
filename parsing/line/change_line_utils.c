/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:37:47 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/22 16:22:37 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_characters(char *s)
{
	while (s[g_glo.i] != '\'' && s[g_glo.i] && s[g_glo.i] != '$' \
	&& s[g_glo.i] != '\"' && s[g_glo.i] != '<')
	{
		g_glo.str = mini_strjoin(g_glo.str, s[g_glo.i]);
		g_glo.i++;
	}
}

void	handle_single_quotes(char *s)
{
	g_glo.tmp = single_double_quotes(s, '\'', &(g_glo.i));
	g_glo.str = f_join(g_glo.str, g_glo.tmp);
	free(g_glo.tmp);
	g_glo.tmp = NULL;
}

void	handle_dollar_signs(char *s)
{
	g_glo.doubleq = 1;
	g_glo.tmp = dollars_money_money(s, &(g_glo.i), 1);
	g_glo.str = f_join(g_glo.str, g_glo.tmp);
	free(g_glo.tmp);
	g_glo.tmp = NULL;
}

void	handle_double_quotes(char *s)
{
	g_glo.str = mini_strjoin(g_glo.str, s[g_glo.i]);
	g_glo.i++;
	while (s[g_glo.i] && s[g_glo.i] != '\"')
	{
		if (s[g_glo.i] == '$')
		{
			g_glo.doubleq = 0;
			g_glo.tmp = dollars_money_money(s, &(g_glo.i), 0);
			g_glo.str = f_join(g_glo.str, g_glo.tmp);
			free(g_glo.tmp);
			g_glo.tmp = NULL;
		}
		else
		{
			g_glo.str = mini_strjoin(g_glo.str, s[g_glo.i]);
			g_glo.i++;
		}
	}
	g_glo.str = mini_strjoin(g_glo.str, s[g_glo.i]);
	g_glo.i++;
}

void	handle_heredoc(char *s)
{
	if (s[g_glo.i] == '<' && s[g_glo.i + 1] == '<')
	{
		while (s[g_glo.i] == '<')
		{
			g_glo.str = mini_strjoin(g_glo.str, s[g_glo.i]);
			g_glo.i++;
		}
		g_glo.tmp = arg_heredoc(s, &(g_glo.i));
		if (g_glo.tmp)
		{
			g_glo.str = mini_strjoin(g_glo.str, 1);
			g_glo.str = f_join(g_glo.str, g_glo.tmp);
			g_glo.str = mini_strjoin(g_glo.str, 1);
		}
		free(g_glo.tmp);
		g_glo.tmp = NULL;
	}
	else
	{
		g_glo.str = mini_strjoin(g_glo.str, s[g_glo.i]);
		g_glo.i++;
	}
}
