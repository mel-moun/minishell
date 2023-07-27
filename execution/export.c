/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:45:01 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/26 15:05:19 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_fnct_norm(void)
{
	t_env	*tmp;
	char	*key;
	char	*value;

	tmp = g_glo.env;
	key = NULL;
	while (tmp)
	{
		if (!ft_strchr(tmp->env, '='))
			printf("declare -x %s\n", tmp->env);
		else
		{
			key = adrs_substr(tmp->env, 0, ft_strchr(tmp->env, '='));
			printf("declare -x %s", key);
			value = expanded_value(key);
			printf("=\"%s\"\n", value);
			free (value);
			value = NULL;
			free (key);
			key = NULL;
		}
		tmp = tmp->next;
	}
}

void	export_fnct(t_all *all, int flag)
{
	int		i;

	i = 1;
	if (!all->cmds[1])
		export_fnct_norm();
	else
	{
		while (all->cmds[i])
		{
			export_fnct_sequel(all, i);
			i++;
		}
	}
	if (flag == 1)
		exit (0);
}

int	export_norm(t_export_var *var, t_all *all, int n)
{
	if (valid_identifier(all->cmds[n]) == 1)
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(all->cmds[n], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_glo.exitstatus = 1;
		return (1);
	}
	var->variable = adrs_substr(all->\
	cmds[n], 0, ft_strchr(all->cmds[n], '='));
	if (var->variable == NULL)
		return (1);
	return (0);
}

int	export_while(t_export_var *var, int n, t_all *all, char	*temp)
{
	t_env			*tmp;

	tmp = g_glo.env;
	while (tmp)
	{
		var->var = \
		adrs_substr(tmp->env, 0, ft_strchr(tmp->env, '='));
		temp = expanded_value(all->cmds[n]);
		if (!ft_strchr(all->cmds[n], '=') && temp)
		{
			free (var->var);
			free (var->variable);
			free (temp);
			return (1);
		}
		if (compare(var->var, var->variable) == 0)
		{
			export_norm_two(&tmp->env, &(*var), all, n);
			return (1);
		}
		free (var->var);
		var->var = NULL;
		tmp = tmp->next;
	}
	return (0);
}

void	export_fnct_sequel(t_all *all, int n)
{
	extern char		**environ;
	int				i;
	char			*temp;
	t_export_var	var;

	i = 0;
	temp = NULL;
	if (export_norm(&var, all, n) == 1)
		return ;
	if (export_while(&var, n, all, temp) == 1)
		return ;
	export_norm_three(all, n, &var);
}
