/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:51:40 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/25 23:29:04 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*read_norm(char **input, t_all *glo, int i, int del)
{
	char	*tmp;
	char	*join;

	tmp = NULL;
	join = NULL;
	while (1)
	{
		*input = readline("> ");
		if (!compare(*input, glo->file_names[i]) || !*input)
			break ;
		if (del == 0)
		{
			tmp = change_heredoc(*input);
			free(*input);
			*input = ft_strdup(tmp);
			free(tmp);
		}
		join = f_join(join, *input);
		join = f_join(join, "\n");
		free(*input);
	}
	return (join);
}

void	read_fnct(t_all *glo, int *pip, int i)
{
	char	*input;
	char	*join;
	char	*tmp;
	int		del;

	tmp = NULL;
	join = NULL;
	close (pip[0]);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGINT, SIG_DFL);
	del = 0;
	if (search_quotes(glo->file_names[i]))
	{
		del = 1;
		tmp = remove_quotes(glo->file_names[i]);
		free(glo->file_names[i]);
		glo->file_names[i] = ft_strdup(tmp);
		free(tmp);
	}
	join = read_norm(&input, glo, i, del);
	write (pip[1], join, ft_strlen(join));
	free(join);
	close(pip[1]);
	exit (0);
}

void	heredoc_fnct_sequel(t_all *all, int *prev, int i)
{
	pid_t	pid;
	int		pip[2];
	int		status;

	pipe(pip);
	signal (SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		read_fnct(all, pip, i);
	all->fd = pip[0];
	close(pip[1]);
	if (*prev)
		close(*prev);
	*prev = pip[0];
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		g_glo.exitstatus = 1;
	else
		g_glo.exitstatus = 0;
	signal (SIGINT, handler_fnct);
	signal (SIGQUIT, SIG_IGN);
}

void	heredoc_fnction(t_all *all)
{
	int		i;
	int		prev;

	while (all)
	{
		i = 0;
		prev = 0;
		if (all->file_names)
		{
			while (all->file_names[i])
			{
				if (all->file_types[i] == HEREDOC)
					heredoc_fnct_sequel(all, &prev, i);
				i++;
			}
		}
		all = all->next;
	}
}
