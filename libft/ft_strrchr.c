/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:32:25 by selkhadr          #+#    #+#             */
/*   Updated: 2022/10/19 23:38:16 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	i = ft_strlen((char *)str);
	if (!str)
		return (NULL);
	while (i >= 0)
	{
		if (((char *)str)[i] == (unsigned char )c)
			return (&((char *)str)[i]);
		i--;
	}
	if (c == 0)
		return (&((char *)str)[i]);
	return (NULL);
}
