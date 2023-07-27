/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:02:23 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/26 11:47:03 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_norm(char *str)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	g_glo.exitstatus = 1;
}

void	unset_norm_two(t_env *temp, t_env *prev)
{
	if (prev != NULL)
		prev->next = temp->next;
	else
		g_glo.env = temp->next;
	free(temp->env);
	free(temp);
}

void	unset_fnct_sequel(char *str)
{
	t_env	*temp;
	t_env	*prev;
	char	*tmp;

	temp = g_glo.env;
	prev = NULL;
	tmp = NULL;
	while (temp != NULL)
	{
		tmp = adrs_substr(temp->env, 0, ft_strchr(temp->env, '='));
		if (compare(tmp, str) == 0)
		{
			free (tmp);
			break ;
		}
		free (tmp);
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	unset_norm_two(temp, prev);
}

void	unset_fnct(t_all *all, int flag)
{
	int			i;

	i = 1;
	while (all->cmds[i])
	{
		unset_fnct_sequel(all->cmds[i]);
		i++;
	}
	if (flag == 1)
		exit (0);
}

int	valid_identifier(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '_')
	{
		if (ft_isalpha(str[0]) == 0)
			return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
