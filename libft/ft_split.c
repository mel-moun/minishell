/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:35:46 by selkhadr          #+#    #+#             */
/*   Updated: 2022/10/20 15:51:02 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len(char *s, char c)
{
	size_t	l;
	size_t	i;

	l = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			l++;
		}
	}
	return (l);
}

char	**ft_split(const char *s, char c)
{
	char	**p;
	size_t	k;
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	if (!s)
		return (NULL);
	p = (char **)malloc((len((char *)s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		k = i;
		while (s[i] && s[i] != c)
			i++;
		if (l < len((char *)s, c))
			p[l++] = ft_substr(s, k, i - k);
	}
	p[l] = NULL;
	return (p);
}
