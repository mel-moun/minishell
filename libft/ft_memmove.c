/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:17:41 by selkhadr          #+#    #+#             */
/*   Updated: 2022/10/19 23:19:56 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == 0 && src == 0)
		return (NULL);
	i = 0;
	if (src < dst)
	{
		while (1 <= len)
		{
			*((char *)dst + (len - 1)) = *((char *)src + (len - 1));
			len--;
		}
	}
	else
		dst = ft_memcpy(dst, src, len);
	return (dst);
}
