/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:23:21 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/25 11:35:23 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	take_env(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_lstadd_back(ft_lstnew(arr[i]));
		i++;
	}
}

void	ft_lstadd_back(t_env *new)
{
	t_env	*tmp;

	tmp = g_glo.env;
	if (g_glo.env == NULL)
	{
		g_glo.env = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*ft_lstnew(char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->env = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	deallocating_env(t_env **ptr)
{
	t_env	*pk;

	if (!ptr || !*ptr)
		return ;
	while (*ptr != NULL)
	{
		pk = *ptr;
		*ptr = (*ptr)->next;
		free(pk->env);
		free(pk);
	}
	*ptr = NULL;
}
