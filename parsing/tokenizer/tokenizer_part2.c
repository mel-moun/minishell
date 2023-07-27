/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:50:27 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/24 15:23:26 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parsing_part_two(t_token **all, t_all **glo)
{
	remove_for(all);
	final_thing(all, glo);
	deallocating(all);
}

void	handle_pipe_case(t_token **all, t_all **gb)
{
	t_token	*curr;

	curr = *all;
	ft_lstaddback_final(gb, ft_lst_final(all));
	while (curr)
	{
		if (curr->type == PIPE)
		{
			curr = curr->next;
			ft_lstaddback_final(gb, ft_lst_final(&curr));
		}
		curr = curr->next;
	}
}

void	final_thing(t_token **all, t_all **gb)
{
	int		pipe;
	t_token	*curr;

	pipe = 0;
	curr = *all;
	while (curr)
	{
		if (curr->type == PIPE)
			pipe++;
		curr = curr->next;
	}
	if (pipe == 0)
	{
		ft_lstaddback_final(gb, ft_lst_final(all));
		return ;
	}
	handle_pipe_case(all, gb);
}

t_all	*ft_lst_final(t_token **all)
{
	t_all	*node;

	node = malloc(sizeof(t_all));
	if (!node)
		return (NULL);
	node->file_types = take_file_types(all);
	node->cmds = take_cmds(all);
	node->file_names = take_file_names(all);
	node->next = NULL;
	return (node);
}
