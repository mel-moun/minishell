/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:51:36 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/22 16:22:37 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	delete_first_node(t_token **head)
{
	t_token	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	*head = (*head)->next;
	free (temp->token);
	free (temp);
}

void	setup_redirections(t_token **curr)
{
	if (((*curr)->type == REDIR_IN || (*curr)->type == REDIR_OUT \
	|| (*curr)->type == APPEND) && (*curr)->next != NULL)
	{
		if ((*curr)->next->type == WORD)
			(*curr)->next->type = FILEE;
	}
}

void	setup_exact_type(t_token **all)
{
	t_token	*curr;
	int		i;

	i = 0;
	curr = *all;
	while (curr != NULL)
	{
		setup_redirections(&curr);
		if (curr->type == WORD)
		{
			if (i == 0)
			{
				curr->type = CMD;
				i = 1;
			}
			else
				curr->type = ARG;
		}
		else if (curr->type == PIPE)
			i = 0;
		curr = curr->next;
	}
}

void	remove_for(t_token **all)
{
	t_token	*curr;
	char	*tmp;

	tmp = NULL;
	curr = *all;
	while (curr)
	{
		if (curr->type == CMD || curr->type == ARG || curr->type == FILEE)
		{
			tmp = remove_quotes(curr->token);
			free(curr->token);
			curr->token = tmp;
		}
		curr = curr->next;
	}
}
