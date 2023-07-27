/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:03:35 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/26 12:13:30 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	take_the_whole_node(char *s, t_token **all)
{
	while (s[g_glo.i] != 32 && s[g_glo.i] != '\t' && s[g_glo.i] != '<' \
	&& s[g_glo.i] != '>' && s[g_glo.i] != '|' \
	&& s[g_glo.i] != 1 && s[g_glo.i] != '\0')
	{
		if (s[g_glo.i] != 32 && s[g_glo.i] != '\t' \
		&& s[g_glo.i] != '<' && s[g_glo.i] != '>' && s[g_glo.i] != '|'\
		&& s[g_glo.i] != 1 && s[g_glo.i] != 31 && s[g_glo.i] != '\0')
			take_the_word(s);
		if (s[g_glo.i] == 31)
			found_expand(s, all);
		if (!(s[g_glo.i] != 32 && s[g_glo.i] != '\t' \
		&& s[g_glo.i] != '<' && s[g_glo.i] != '>' \
		&& s[g_glo.i] != '|' && s[g_glo.i] != 1))
			break ;
	}
	take_node(all);
}

void	take_arg_heredoc(char *s, t_token **all)
{
	g_glo.tmp = single_double_quotes(s, 1, &g_glo.i);
	g_glo.str = ft_substr(g_glo.tmp, 1, ft_strlen(g_glo.tmp) - 2);
	lstaddback_token(all, lstnew_token(g_glo.str, S_ARG));
	free(g_glo.tmp);
	free(g_glo.str);
	g_glo.tmp = NULL;
	g_glo.str = NULL;
}

void	take_pipe(t_token **all)
{
	lstaddback_token(all, lstnew_token("|", PIPE));
	g_glo.i++;
}

void	take_append(char *s, t_token **all)
{
	if (s[g_glo.i + 1] == '>')
	{
		while (s[g_glo.i] == '>')
		{
			g_glo.len++;
			g_glo.i++;
		}
		if (g_glo.len == 2)
			lstaddback_token(all, lstnew_token(">", APPEND));
		else
			lstaddback_token(all, lstnew_token(">", APPEND_ERROR));
	}
	else
	{
		lstaddback_token(all, lstnew_token(">", REDIR_OUT));
		g_glo.i++;
	}
	g_glo.len = 0;
}

void	take_heredoc(t_token **all, char *s)
{
	if (s[g_glo.i + 1] == '<')
	{
		while (s[g_glo.i] == '<')
		{
			g_glo.len++;
			g_glo.i++;
		}
		if (g_glo.len == 2)
			lstaddback_token(all, lstnew_token("<", HEREDOC));
		else
			lstaddback_token(all, lstnew_token("<", HEREDOC_ERROR));
	}
	else
	{
		lstaddback_token(all, lstnew_token("<", REDIR_IN));
		g_glo.i++;
	}
	g_glo.len = 0;
}
