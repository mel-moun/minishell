/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:45:43 by selkhadr          #+#    #+#             */
/*   Updated: 2022/10/20 00:52:16 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	len(long n)
{
	long	i;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*fnct(long m, int l, char *r)
{
	int	i;
	int	j;

	i = 0;
	if (m == 0)
		r[0] = '0';
	if (m < 0)
	{
		r[0] = '-';
		m = -m;
		i++;
	}
	j = l -1;
	while (j >= i)
	{
		r[j] = m % 10 + '0';
		m /= 10;
		j--;
	}
	r[l] = '\0';
	return (r);
}

char	*ft_itoa(int n)
{
	long	m;
	char	*r;
	int		l;

	m = n;
	l = len(m);
	r = (char *)malloc((l + 1) * sizeof(char));
	if (r == 0)
		return (0);
	r = fnct(m, l, r);
	return (r);
}
