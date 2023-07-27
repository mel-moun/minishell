/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:51:30 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/26 11:52:42 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	use_builtins_sequel(t_all *all)
{
	if (!all || !all->cmds || !all->cmds[0])
		return (0);
	if (all->cmds[0] && compare(all->cmds[0], "export") == 0 && all->cmds[1])
	{
		export_fnct(all, 0);
		return (1);
	}
	else if (all->cmds[0] && compare(all->cmds[0], "unset") == 0)
	{
		unset_fnct(all, 0);
		return (1);
	}
	else if (compare(all->cmds[0], "cd") == 0)
	{
		chdir_fnct(all, 0);
		return (1);
	}
	else if (compare(all->cmds[0], "exit") == 0)
		return (exit_fnct(all));
	return (0);
}

void	use_builtins(t_all *all)
{
	char	pwd[1000];

	if (!all || !all->cmds || !all->cmds[0])
		return ;
	else if (compare(all->cmds[0], "export") == 0)
		export_fnct(all, 1);
	else if (compare(all->cmds[0], "unset") == 0)
		unset_fnct(all, 1);
	else if (compare(all->cmds[0], "echo") == 0)
		echo_fnct(all, 1);
	else if (compare(all->cmds[0], "pwd") == 0)
	{
		if (getcwd(pwd, PATH_MAX) != NULL)
			printf("%s\n", pwd);
		exit (0);
	}
	else if (compare(all->cmds[0], "env") == 0)
		print_env(1);
}
