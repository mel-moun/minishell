/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_linked1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:50:49 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/26 16:23:15 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_cmds(t_all *pk)
{
	int	i;

	i = -1;
	while (pk->cmds[++i])
		free(pk->cmds[i]);
	free(pk->cmds);
}

void	free_file_names(t_all *pk)
{
	int	i;

	i = -1;
	while (pk->file_names[++i])
		free(pk->file_names[i]);
	free(pk->file_names);
}

void	clear_all(t_all **ptr)
{
	t_all	*pk;

	if (!ptr || !*ptr)
		return ;
	while (*ptr != NULL)
	{
		pk = *ptr;
		*ptr = (*ptr)->next;
		free(pk->file_types);
		if (pk->cmds)
			free_cmds(pk);
		if (pk->file_names)
			free_file_names(pk);
		free(pk);
	}
	*ptr = NULL;
}

int	whats_next(int check)
{
	if (check == PIPE || check == REDIR_OUT)
		return (1);
	if (check == APPEND || check == HEREDOC_ERROR)
		return (1);
	if (check == HEREDOC || check == APPEND_ERROR)
		return (1);
	if (check == REDIR_IN)
		return (1);
	return (0);
}

int	syntax_error_first(t_token **all)
{
	t_token	*curr;

	curr = *all;
	if (curr->type == PIPE)
		return (1);
	while (curr != NULL && curr->next != NULL)
	{
		if (curr->type == REDIR_IN && whats_next(curr->next->type))
			return (1);
		if (curr->type == REDIR_OUT && whats_next(curr->next->type))
			return (1);
		if (curr->type == APPEND && whats_next(curr->next->type))
			return (1);
		if (curr->type == HEREDOC && whats_next(curr->next->type))
			return (1);
		if (curr->type == APPEND_ERROR || curr->type == HEREDOC_ERROR)
			return (1);
		if (curr->type == PIPE && curr->next->type == PIPE)
			return (1);
		curr = curr->next;
	}
	if (whats_next(curr->type) || curr->type == PIPE)
		return (1);
	return (0);
}
