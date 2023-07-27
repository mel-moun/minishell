/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:53:20 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/26 12:00:24 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_empty_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	print_env(int flag)
{
	int			i;
	t_env		*tmp;

	i = 0;
	tmp = g_glo.env;
	while (tmp)
	{
		if (ft_strchr(tmp->env, '=') != NULL)
			printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
	if (flag == 1)
		exit (0);
}

int	only_n_alpha(char *str)
{
	int	i;

	i = 1;
	if (str == NULL)
		return (1);
	if (str[0] != '-')
		return (1);
	if (str[0] == '-' && !str[1])
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_fnct(t_all *all, int flag)
{
	int	i;
	int	fg;

	i = 1;
	fg = 0;
	while (only_n_alpha(all->cmds[i]) == 0)
	{
		i++;
		fg = 1;
	}
	while (all->cmds[i])
	{
		ft_putstr_fd(all->cmds[i], 1);
		if (all->cmds[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (fg == 0)
		write (1, "\n", 1);
	if (flag == 1)
		exit (0);
}
