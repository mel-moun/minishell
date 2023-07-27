/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_linked.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:48:31 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/26 12:13:30 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_token	*lstnew_token(char *content, int value)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = ft_strdup(content);
	node->type = value;
	node->next = NULL;
	return (node);
}

void	lstaddback_token(t_token **lst, t_token *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next != NULL)
		lst = &(*lst)->next;
	(*lst)->next = new;
}

void	ft_lstaddback_final(t_all **lst, t_all *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next != NULL)
		lst = &(*lst)->next;
	(*lst)->next = new;
}

void	dollar_lhgar(t_token **all, char *s)
{
	int		i;
	char	**line;

	i = 0;
	line = mer_split(s);
	while (line[i])
	{
		lstaddback_token(all, lstnew_token(line[i], WORD));
		i++;
	}
	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}
