/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_linked3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:52:28 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/24 16:54:00 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	join_linked_list(t_token **all, t_token **otherall)
{
	t_token	*current;

	if (*all == NULL)
	{
		*all = *otherall;
		return ;
	}
	current = *all;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = *otherall;
	*otherall = NULL;
}

void	deallocating(t_token **ptr)
{
	t_token	*pk;

	if (!ptr || !*ptr)
		return ;
	while (*ptr != NULL)
	{
		pk = *ptr;
		*ptr = (*ptr)->next;
		free(pk->token);
		free(pk);
	}
	*ptr = NULL;
}
