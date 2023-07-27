/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:47:44 by selkhadr          #+#    #+#             */
/*   Updated: 2022/10/20 01:52:40 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	skip_spaces(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	signe(char *p, int *s)
{
	if (*p == '+' && ft_isdigit(*(p + 1)))
		return (1);
	if (*p == '-' && ft_isdigit(*(p + 1)))
	{
		*s = -1;
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	r;
	int	s;

	i = 0;
	r = 0;
	s = 1;
	while (((char *)str)[i])
	{
		while (skip_spaces(((char *)str)[i]))
			i++;
		if (signe((char *)str + i, &s))
			i++;
		while (ft_isdigit(((char *)str)[i]))
			r = r * 10 + (((char *)str)[i++] - 48);
		break ;
	}
	return (r * s);
}
