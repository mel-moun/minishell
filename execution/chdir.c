/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:20:31 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/26 15:52:55 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(void)
{
	t_env	*tmp;
	char	pwd[1000];
	char	*var;

	var = NULL;
	tmp = g_glo.env;
	getcwd(pwd, PATH_MAX);
	while (tmp->env)
	{
		var = adrs_substr(tmp->env, 0, ft_strchr(tmp->env, '='));
		if (compare(var, "PWD") == 0)
		{
			free (tmp->env);
			tmp->env = NULL;
			free (var);
			tmp->env = ft_strjoin("PWD=", pwd);
			break ;
		}
		free (var);
		var = NULL;
		tmp = tmp->next;
	}
}

int	chdir_norm(t_all *all)
{
	DIR	*dir;

	dir = opendir(all->cmds[1]);
	if (dir == NULL && access(all->cmds[1], F_OK) == 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(all->cmds[1], 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (1);
	}
	if (dir != NULL)
		closedir(dir);
	if (chdir(all->cmds[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(all->cmds[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_glo.exitstatus = 1;
		return (1);
	}
	change_pwd();
	return (0);
}

void	chdir_fnct(t_all *all, int flag)
{
	char	*tmp;

	tmp = expanded_value("HOME");
	if (all->cmds[1] == NULL || !compare(all->cmds[1], "~"))
	{
		if (!tmp)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_glo.exitstatus = 1;
			return ;
		}
		chdir (tmp);
		change_pwd();
	}
	else
	{
		if (chdir_norm(all) == 1)
		{
			free (tmp);
			return ;
		}
	}
	free (tmp);
	if (flag == 1)
		exit (0);
}
