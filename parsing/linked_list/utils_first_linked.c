/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_first_linked.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:06:38 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/26 12:13:30 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	initialization_of_vars(void)
{
	g_glo.i = 0;
	g_glo.j = 0;
	g_glo.k = 0;
	g_glo.node = NULL;
	g_glo.str = NULL;
	g_glo.tmp = NULL;
	g_glo.test = NULL;
	g_glo.curr = NULL;
	g_glo.len = 0;
}

void	take_the_word(char *s)
{
	g_glo.tmp = take_everything(s, &g_glo.i);
	g_glo.node = f_join(g_glo.node, g_glo.tmp);
	free(g_glo.tmp);
	g_glo.tmp = NULL;
}

void	take_node(t_token **all)
{
	if (g_glo.node)
		lstaddback_token(all, lstnew_token(g_glo.node, WORD));
	free(g_glo.node);
	g_glo.node = NULL;
}

void	treatment(char *s, t_token **all)
{
	if (g_glo.node && s[g_glo.j - 1] != '\t' && s[g_glo.j - 1] != 32)
	{
		lstaddback_token(all, lstnew_token(g_glo.node, WORD));
		free(g_glo.node);
		g_glo.node = NULL;
	}
	if ((!*all || !all) && !g_glo.node)
		lstaddback_token(all, lstnew_token("", WORD));
	dollar_lhgar(&g_glo.test, g_glo.str);
	free(g_glo.str);
	g_glo.str = NULL;
	if (g_glo.i - ft_strlen(g_glo.tmp) > 0)
	{
		g_glo.j = g_glo.i - ft_strlen(g_glo.tmp);
		if ((s[g_glo.j - 1] != ' ' && s[g_glo.j - 1] != '\t'))
		{
			g_glo.curr = ft_lstlast(*all);
			g_glo.curr->token = f_join(g_glo.curr->token, g_glo.test->token);
			delete_first_node(&g_glo.test);
		}
	}
	free(g_glo.tmp);
	g_glo.tmp = NULL;
	join_linked_list(all, &g_glo.test);
}
