/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:21:56 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/26 12:03:52 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*dollar_then_quotes(int count, char *s)
{
	if (count % 2 != 0)
		add_dollar_char(count - 1);
	else
		add_dollar_char(count);
	g_glo.tmp = single_double_quotes(s, s[g_glo.i], &g_glo.i);
	g_glo.to_expand = f_join(g_glo.to_expand, g_glo.tmp);
	free(g_glo.tmp);
	g_glo.tmp = NULL;
	return (g_glo.to_expand);
}

char	*expand_normal(int count, int *i)
{
	if (count % 2 != 0)
		g_glo.to_expand = expand_the_var(count);
	else
	{
		add_dollar_char(count);
		g_glo.to_expand = f_join(g_glo.to_expand, g_glo.before);
	}
	*i = g_glo.j;
	free(g_glo.before);
	g_glo.before = NULL;
	return (g_glo.to_expand);
}

char	*expand_the_var(int count)
{
	if (is_digit(g_glo.before[0]))
		return (dollar_then_digit(count));
	add_dollar_char(count - 1);
	g_glo.tmp = expanded_value(g_glo.before);
	if (!g_glo.tmp)
		g_glo.to_expand = f_join(g_glo.to_expand, "");
	else if (g_glo.doubleq)
	{
		g_glo.to_expand = mini_strjoin(g_glo.to_expand, 31);
		g_glo.to_expand = f_join(g_glo.to_expand, g_glo.tmp);
		g_glo.to_expand = mini_strjoin(g_glo.to_expand, 31);
	}
	else
		g_glo.to_expand = f_join(g_glo.to_expand, g_glo.tmp);
	free(g_glo.tmp);
	g_glo.tmp = NULL;
	return (g_glo.to_expand);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*dollar_then_digit(int count)
{
	g_glo.i = g_glo.j;
	if (count % 2 != 0)
		add_dollar_char(count - 1);
	else
		add_dollar_char(count);
	g_glo.tmp = ft_substr(g_glo.before, 1, ft_strlen(g_glo.before));
	g_glo.to_expand = f_join(g_glo.to_expand, g_glo.tmp);
	free(g_glo.tmp);
	free(g_glo.before);
	g_glo.tmp = NULL;
	g_glo.before = NULL;
	return (g_glo.to_expand);
}
