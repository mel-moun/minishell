/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:58:13 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/22 16:22:37 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	count_files(t_token **all, int *count)
{
	*count = 0;
	g_glo.curr = *all;
	while (g_glo.curr && g_glo.curr->type != PIPE)
	{
		if (g_glo.curr->type == FILEE || g_glo.curr->type == S_ARG)
			(*count)++;
		g_glo.curr = g_glo.curr->next;
	}
}

char	**take_file_names(t_token **all)
{
	int		count;
	int		i;
	char	**full;

	count_files(all, &count);
	full = NULL;
	i = 0;
	if (count == 0)
		return (NULL);
	full = (char **)malloc(sizeof(char *) * (count + 1));
	if (!full)
		return (NULL);
	g_glo.curr = *all;
	while (g_glo.curr && g_glo.curr->type != PIPE)
	{
		if (g_glo.curr->type == FILEE || g_glo.curr->type == S_ARG)
		{
			if (!empty(g_glo.curr->token) && g_glo.curr->token)
				full[i++] = ft_strdup(g_glo.curr->token);
		}
		g_glo.curr = g_glo.curr->next;
	}
	full[i] = NULL;
	return (full);
}

void	delete_empty_nodes(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current != NULL && !ft_strcmp(current->token, ""))
	{
		*head = current->next;
		free(current->token);
		free(current);
		current = *head;
	}
}
