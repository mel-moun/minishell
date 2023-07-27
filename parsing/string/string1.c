/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:42:41 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/26 16:24:00 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_single_double(char *s)
{
	int	i;
	int	ddouble;
	int	single;

	i = 0;
	ddouble = 0;
	single = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			single++;
		else if (s[i] == '\"')
			ddouble++;
		i++;
	}
	if (single % 2 != 0 || ddouble % 2 != 0)
		return (-1);
	return (0);
}

char	*single_double_quotes(char *s, char c, int *i)
{
	int		len;
	int		j;
	int		tmp;
	char	*tmp1;

	len = 0;
	j = *i + 1;
	tmp = *i;
	while (s[j] != c && s[j])
	{
		j++;
		len++;
	}
	if (s[j] != c)
	{
		*i = j;
		return (ft_substr(s, tmp, len + 1));
	}
	*i = j + 1;
	tmp1 = ft_substr(s, tmp, len + 2);
	return (tmp1);
}

char	*take_word(char *s, int *i)
{
	int	len;
	int	j;
	int	tmp;

	len = 0;
	j = *i;
	tmp = *i;
	while (s[j] && s[j] != '|' && s[j] != '<' \
	&& s[j] != '>' && s[j] != 32 && s[j] != '\t' \
	&& s[j] != 1 && s[j] != 31 \
	&& s[j] != '\'' && s[j] != '\"')
	{
		j++;
		len++;
	}
	*i = j;
	return (ft_substr(s, tmp, len));
}

char	*f_join(char *s1, char *s2)
{
	int		i;
	char	*p;
	int		j;

	i = -1;
	j = 0;
	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s2)
		return (NULL);
	p = (char *) malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen (s2)) + 1);
	if (p == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		p[i] = s1[i];
	while (s2[j] != '\0')
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	free(s1);
	return (p);
}
