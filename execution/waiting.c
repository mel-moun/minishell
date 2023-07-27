/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:40:50 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/26 12:54:50 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_fnct(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	close_pipes(t_all *all)
{
	if (all->prev_pip != 0)
		close(all->prev_pip);
	if (all->next)
		close(all->pip[1]);
}

void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free (ptr[i++]);
	free (ptr);
}

void	waiting_norm(t_all *glo)
{
	int	tmp;

	if (compare(glo->cmds[0], "exit") == 0)
	{
		printf("ddd = %d\n", g_glo.exitstatus);
		if (!glo->cmds[1])
		{	
			tmp = g_glo.exitstatus;
			error_message(0, NULL);
			exit (tmp);
		}
		if ((is_num(glo->cmds[1]) && !glo->cmds[2]) || !is_num(glo->cmds[1]))
		{
			tmp = g_glo.exitstatus;
			error_message(0, NULL);
			exit (tmp);
		}
	}
}

void	waiting_fnct(t_all *glo)
{
	int	status;

	while (glo)
	{
		waitpid(glo->pid, &status, 0);
		signal (SIGINT, handler_fnct);
		signal (SIGQUIT, SIG_IGN);
		if (WIFEXITED(status))
		{
			g_glo.exitstatus = WEXITSTATUS(status);
			if (glo->cmds != NULL)
				waiting_norm(glo);
		}
		else if (WIFSIGNALED(status))
			g_glo.exitstatus = WTERMSIG(status) + 128;
		glo = glo->next;
	}
}
