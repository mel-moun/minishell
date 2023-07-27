/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:15:32 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/23 18:02:44 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*dollars_money_money(char *s, int *i, int sp)
{
	int	count;

	g_glo.to_expand = NULL;
	count = count_dollar_char(s);
	if (s[g_glo.j] == '?' && g_glo.len == 0)
		return (expand_exit_status(count));
	if (s[g_glo.j] == '@' && g_glo.len == 0 && count % 2 != 0)
		return (expand_arobase(count, g_glo.len, s));
	if (s[g_glo.i - 1] == '$' && (s[g_glo.i] == '\'' \
	|| s[g_glo.i] == '\"') && sp)
		return (dollar_then_quotes(count, s));
	if (g_glo.len == 0)
	{
		add_dollar_char(count);
		g_glo.i = g_glo.j;
		return (g_glo.to_expand);
	}
	g_glo.before = ft_substr(s, g_glo.i, g_glo.len);
	return (expand_normal(count, i));
}

char	*expanded_value(char *s)
{
	t_env	*curr;
	char	*str;
	int		i;

	curr = g_glo.env;
	i = 0;
	while (curr)
	{
		str = curr->env;
		if (ft_strlen(str) >= ft_strlen(s) \
		&& mer_strncmp(s, str, ft_strlen(s)) == 0 \
		&& str[ft_strlen(s)] == '=')
		{
			i = ft_strlen(s) + 1;
			return (ft_substr(str, i, ft_strlen(&str[i])));
		}
		curr = curr->next;
	}	
	return (NULL);
}
