/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:04:18 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/26 11:56:11 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	use_execve(t_all *all, char **env)
{
	if (!all || !all->path || !all->cmds)
		exit (1);
	execve(all->path, all->cmds, env);
	perror ("execve");
	exit (g_glo.exitstatus);
}

void	close_heredoc(t_all *all)
{
	t_all	*tmp;

	tmp = all;
	while (tmp)
	{
		if (check_redirct(tmp, HEREDOC))
			close(tmp->fd);
		tmp = tmp->next;
	}
}
