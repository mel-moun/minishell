/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:04:41 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/24 15:23:52 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	closed_double_quotes(char *s)
{
	int		i;
	char	c;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				i++;
			if (s[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

char	*arg_heredoc_support(char *s, int *j, char *arg)
{
	char	*tmp;

	tmp = NULL;
	while (s[*j] != '|' && s[*j] != '\t' \
	&& s[*j] != 32 && s[*j] != '>' \
	&& s[*j] != '<' && s[*j])
	{
		if (s[*j] == '\'' || s[*j] == '\"')
		{
			tmp = single_double_quotes(s, s[*j], j);
			arg = f_join(arg, tmp);
			free(tmp);
		}
		else
		{
			arg = mini_strjoin(arg, s[*j]);
			(*j)++;
		}
	}
	return (arg);
}

char	*arg_heredoc(char *s, int *i)
{
	char	*arg;
	int		j;
	char	*tmp;

	arg = NULL;
	j = *i;
	tmp = NULL;
	while (s[j] == 32 || s[j] == '\t')
		j++;
	if (!s[j])
		return (NULL);
	arg = arg_heredoc_support(s, &j, arg);
	if (arg)
		*i = j;
	return (arg);
}
