/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:27:29 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/26 12:55:14 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_fnct(t_all *all)
{
	if (all->next)
	{
		all->next->prev_pip = 0;
		if (pipe(all->pip) == -1)
			exit (-1);
		all->next->prev_pip = all->pip[READ];
	}
}

void	execution_fnct_sequel(t_all *all, char **env)
{
	if (all->pid == -1)
		exit (-1);
	if (all->pid == 0)
	{
		signal (SIGQUIT, SIG_IGN);
		signal (SIGINT, SIG_DFL);
		out_redirect(all);
		in_redirect(all);
		if (all->next)
		{
			close(all->pip[WRIT]);
			close(all->pip[READ]);
		}
		if (all->prev_pip != 0)
			close(all->prev_pip);
		use_builtins(all);
		check_path(all);
		use_execve(all, env);
	}
	close_pipes(all);
}

void	execution_fnct(t_all *glo, char **env)
{
	t_all	*tmp;

	tmp = glo;
	g_glo.exitstatus = 0;
	heredoc_fnction(glo);
	if (glo->next == NULL)
	{
		if (use_builtins_sequel(tmp) == 1)
			return ;
	}
	while (tmp)
	{
		pipe_fnct(tmp);
		signal (SIGINT, SIG_IGN);
		tmp->pid = fork();
		execution_fnct_sequel(tmp, env);
		tmp = tmp->next;
	}
	tmp = glo;
	close_heredoc(tmp);
	waiting_fnct(tmp);
}
