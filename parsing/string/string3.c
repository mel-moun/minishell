/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:44:41 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/22 16:22:37 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_quotes(char *s)
{
	int		i;
	char	*all;

	i = 0;
	all = NULL;
	g_glo.tmp = NULL;
	g_glo.str = NULL;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] != '\'' && s[i] != '\"')
		{
			all = mini_strjoin(all, s[i]);
			i++;
		}
		if (s[i] == '\'' || s[i] == '\"')
		{
			g_glo.tmp = single_double_quotes(s, s[i], &i);
			g_glo.str = ft_substr(g_glo.tmp, 1, ft_strlen(g_glo.tmp) - 2);
			all = f_join(all, g_glo.str);
			free(g_glo.tmp);
			free(g_glo.str);
		}
	}
	return (all);
}

int	char_belongs_to(char c)
{
	if (c && c != '|' && c != '<' \
	&& c != '>' && c != 32 && c != '\t' \
	&& c != 1 && c != 31 \
	&& c != '\'' && c != '\"')
		return (1);
	return (0);
}

int	char_dont_belong_to(char c)
{
	if (!(c && c != '|' && c != '<' \
	&& c != '>' && c != 32 \
	&& c != '\t' && c != 1 && c != 31))
		return (1);
	return (0);
}

char	*take_everything(char *s, int *i)
{
	char	*exp;

	g_glo.tmp = NULL;
	exp = NULL;
	while (s[*i])
	{
		if (char_belongs_to(s[*i]))
		{
			g_glo.tmp = take_word(s, i);
			exp = f_join(exp, g_glo.tmp);
			free(g_glo.tmp);
			g_glo.tmp = NULL;
		}
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			g_glo.tmp = single_double_quotes(s, s[*i], i);
			exp = f_join(exp, g_glo.tmp);
			free(g_glo.tmp);
			g_glo.tmp = NULL;
		}
		if (char_dont_belong_to(s[*i]))
			break ;
	}
	return (exp);
}

char	*mini_strjoin(char *s, char c)
{
	char	*p;
	int		i;

	if (!s)
	{
		s = malloc(1);
		if (!s)
			return (NULL);
		s[0] = '\0';
	}
	p = malloc(ft_strlen(s) + 2);
	if (!p)
		return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = c;
	i++;
	p[i] = '\0';
	free(s);
	return (p);
}
