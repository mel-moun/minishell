/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:19:25 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/22 16:22:37 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_dollar_char(char *s)
{
	int	count;

	g_glo.len = 0;
	count = 0;
	while (s[g_glo.i] == '$')
	{
		(g_glo.i)++;
		count++;
	}
	g_glo.j = g_glo.i;
	while (s[g_glo.j] && alphabetic(s[g_glo.j]))
	{
		g_glo.len++;
		g_glo.j++;
	}
	return (count);
}

int	alphabetic(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	|| c == '_' || is_digit(c))
		return (1);
	return (0);
}

char	*expand_exit_status(int count)
{
	if (count % 2 != 0)
	{
		add_dollar_char(count - 1);
		g_glo.tmp = ft_itoa(g_glo.exitstatus);
		g_glo.to_expand = f_join(g_glo.to_expand, g_glo.tmp);
		free(g_glo.tmp);
		g_glo.tmp = NULL;
	}
	else
	{
		add_dollar_char(count);
		g_glo.to_expand = f_join(g_glo.to_expand, "?");
	}
	g_glo.i = g_glo.j + 1;
	return (g_glo.to_expand);
}

void	add_dollar_char(int count)
{
	while (count)
	{
		g_glo.to_expand = mini_strjoin(g_glo.to_expand, '$');
		count--;
	}
}

char	*expand_arobase(int count, int len, char *s)
{
	g_glo.j++;
	g_glo.i = g_glo.j;
	while (s[g_glo.j] && alphabetic(s[g_glo.j]))
	{
		len++;
		g_glo.j++;
	}
	if (count % 2 != 0)
		add_dollar_char(count - 1);
	else
		add_dollar_char(count);
	g_glo.tmp = ft_substr(s, g_glo.i, len);
	g_glo.to_expand = f_join(g_glo.to_expand, g_glo.tmp);
	free(g_glo.tmp);
	g_glo.tmp = NULL;
	g_glo.i = g_glo.j;
	return (g_glo.to_expand);
}
