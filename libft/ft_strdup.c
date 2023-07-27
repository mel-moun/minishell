/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:43:32 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/23 17:57:25 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	if (!s1)
		return (NULL);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (0);
	while (i < len)
	{
		p[i] = ((char *)s1)[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
