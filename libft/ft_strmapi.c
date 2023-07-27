/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:03:50 by selkhadr          #+#    #+#             */
/*   Updated: 2022/10/20 01:04:52 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int n, char c))
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	p = (char *)malloc(ft_strlen(s) + 1 * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = 0;
	return (p);
}
