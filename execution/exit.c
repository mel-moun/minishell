/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:52:08 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/26 12:51:22 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	compare(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}

int	is_num(char *ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (0);
	if (ptr[i] == '-' || ptr[i] == '+')
		i++;
	if (ptr[i] == 0)
		return (0);
	else
	{
		while (ptr[i])
		{
			if (!(ptr[i] >= '0' && ptr[i] <= '9'))
				return (0);
			i++;
		}
	}
	return (1);
}

void	exit_norm(t_all *all)
{
	if (all->cmds[1] == NULL)
	{
		printf("exit\n");
		exit (g_glo.exitstatus);
	}
	if (is_num(all->cmds[1]) && !all->cmds[2])
	{
		printf("exit\n");
		exit (ft_atoi(all->cmds[1]));
	}
}

int	exit_fnct(t_all *all)
{
	exit_norm(all);
	if (is_num(all->cmds[1]) && all->cmds[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		g_glo.exitstatus = 1;
		return (1);
	}
	else if (is_num(all->cmds[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(all->cmds[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit (255);
	}
	return (0);
}
