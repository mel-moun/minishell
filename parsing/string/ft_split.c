/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:08:31 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/23 17:50:06 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check( char *s)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == '\t' || s[i] == 32) && s[i] != '\0')
			i++;
		if (s[i] != '\t' && s[i] != 32 && s[i] != '\0')
			count++;
		while (s[i] != '\t' && s[i] != 32 && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	**writeplz( char *s, char **p, unsigned char i)
{
	unsigned int	j;
	unsigned int	k;
	size_t			len;

	j = 0;
	k = 0;
	len = 0;
	while (s[i] != '\0')
	{
		while (s[i] == '\t' || s[i] == 32)
			i++;
		j = i - 1;
		while (s[++j] != '\t' && s[j] != 32 && s[j] != '\0')
			len++;
		if (s[i] == '\0')
		{
			p[k] = 0;
			break ;
		}
		p[k++] = ft_substr(s, i, len);
		len = 0;
		i = j;
	}
	return (p);
}

char	**mer_split(char *s)
{
	char			**p;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	p = (char **) ft_calloc ((check(s) + 1), sizeof(char *));
	if (p == NULL)
		return (NULL);
	return (writeplz(s, p, i));
}
