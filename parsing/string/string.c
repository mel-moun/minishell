/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:40:14 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/26 16:29:06 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	empty(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '\0' || !s)
		return (1);
	while (s[i] == '\t' || s[i] == 32)
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int	mer_strncmp(char *ss1, char *ss2, int n)
{
	int	i;

	i = 0;
	while (i < n && (ss2[i] != '\0' && ss1[i] != '\0'))
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}
