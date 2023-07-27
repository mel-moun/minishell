/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_first_linked.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:32:14 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/22 16:22:37 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	take_expanded(char *s)
{
	g_glo.j = g_glo.i;
	g_glo.k = g_glo.i;
	g_glo.tmp = single_double_quotes(s, 31, &g_glo.i);
	g_glo.str = ft_substr(g_glo.tmp, 1, ft_strlen(g_glo.tmp) - 2);
}

void	take_one_expanded(void)
{
	g_glo.node = f_join(g_glo.node, g_glo.str);
	free(g_glo.str);
	g_glo.str = NULL;
	free(g_glo.tmp);
	g_glo.tmp = NULL;
}

void	search_to_expand(char *s)
{
	g_glo.j = g_glo.i;
	g_glo.tmp = single_double_quotes(s, 31, &g_glo.j);
	g_glo.str = ft_substr(g_glo.tmp, 1, ft_strlen(g_glo.tmp) - 2);
}

int	take_alot_expanded_count(char *s)
{
	if (s[g_glo.i] != 32 && s[g_glo.i] != '\t' \
	&& s[g_glo.i] != '<' && s[g_glo.i] != '>' \
	&& s[g_glo.i] != '|' && s[g_glo.i] != 1 && s[g_glo.i] != '\0')
		return (1);
	return (0);
}

void	take_a_lot_expanded(char *s)
{
	while (take_alot_expanded_count(s))
	{
		if (s[g_glo.i] != 31)
		{
			g_glo.tmp = take_everything(s, &g_glo.i);
			g_glo.curr->token = f_join(g_glo.curr->token, g_glo.tmp);
			free_tmp_str();
		}
		else if (s[g_glo.i] == 31)
		{
			search_to_expand(s);
			if (check(g_glo.str) == 1)
			{
				g_glo.curr->token = f_join(g_glo.curr->token, g_glo.tmp);
				g_glo.i = g_glo.j;
			}
			else
			{
				free_tmp_str();
				break ;
			}
			free_tmp_str();
		}
	}
}
