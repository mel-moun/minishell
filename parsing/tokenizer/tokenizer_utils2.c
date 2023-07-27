/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:54:40 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/22 16:22:37 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	count_redirections(t_token **all, int *count)
{
	(*count) = 0;
	g_glo.curr = *all;
	while (g_glo.curr && g_glo.curr->type != PIPE)
	{
		if (g_glo.curr->type == REDIR_IN || g_glo.curr->type == REDIR_OUT \
		|| g_glo.curr->type == HEREDOC || g_glo.curr->type == APPEND)
			(*count)++;
		g_glo.curr = g_glo.curr->next;
	}
}

int	*take_file_types(t_token **all)
{
	int	count;
	int	*types;
	int	i;

	i = 0;
	count_redirections(all, &count);
	if (count == 0)
		return (NULL);
	types = (int *)malloc(sizeof(int) * (count));
	if (!types)
		return (NULL);
	g_glo.curr = *all;
	while (g_glo.curr && g_glo.curr->type != PIPE)
	{
		if (g_glo.curr->type == REDIR_IN || g_glo.curr->type == REDIR_OUT \
		|| g_glo.curr->type == HEREDOC || g_glo.curr->type == APPEND)
		{
			types[i] = g_glo.curr->type;
			i++;
		}
		g_glo.curr = g_glo.curr->next;
	}
	return (types);
}

void	count_cmds_args(t_token **all, int *count)
{
	(*count) = 0;
	g_glo.curr = *all;
	while (g_glo.curr && g_glo.curr->type != PIPE)
	{
		if (g_glo.curr->type == CMD || g_glo.curr->type == ARG)
			(*count)++;
		g_glo.curr = g_glo.curr->next;
	}
}

char	**take_cmds(t_token **all)
{
	int		count;
	int		i;
	char	**full;

	i = 0;
	count_cmds_args(all, &count);
	full = NULL;
	if (count == 0)
		return (NULL);
	full = (char **)malloc(sizeof(char *) * (count + 1));
	if (!full)
		return (NULL);
	g_glo.curr = *all;
	while (g_glo.curr && g_glo.curr->type != PIPE)
	{
		if (g_glo.curr->type == CMD || g_glo.curr->type == ARG)
		{
			if (g_glo.curr->token)
				full[i++] = ft_strdup(g_glo.curr->token);
		}
		g_glo.curr = g_glo.curr->next;
	}
	full[i] = NULL;
	return (full);
}
