/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sequel_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:46:17 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/26 11:50:14 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_norm_two(char **env, t_export_var *var, t_all *all, int n)
{
	free ((*env));
	(*env) = NULL;
	(*env) = ft_strdup(all->cmds[n]);
	free(var->var);
	var->var = NULL;
	free(var->variable);
	var->variable = NULL;
}

void	export_norm_three(t_all *all, int n, t_export_var *var)
{
	free (var->variable);
	var->variable = NULL;
	ft_lstadd_back(ft_lstnew(all->cmds[n]));
}

char	*adrs_substr(char *s, int start, char *t)
{
	char	*p;
	int		i;
	int		len;

	i = 0;
	if (!t)
		return (ft_strdup(s));
	len = t - s;
	if (!s)
		return (NULL);
	if (start >= (int)ft_strlen(s))
		return (ft_calloc(1, 1));
	if ((int)ft_strlen(s) < len)
		p = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s[start] && i < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
