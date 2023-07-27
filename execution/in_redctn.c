/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redctn_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:56:41 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/25 16:02:34 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redirct(t_all *tmp, int flag)
{
	int	i;

	i = 0;
	if (!tmp)
		return (0);
	while (tmp->file_names && tmp->file_names[i])
	{
		if (tmp->file_types[i] == flag)
			return (1);
		i++;
	}
	return (0);
}

int	last_input(t_all *tmp)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (tmp->file_names[i])
	{
		if (tmp->file_types[i] == REDIR_IN || tmp->file_types[i] == HEREDOC)
			last = i;
		if (tmp->file_types[i] == REDIR_IN)
		{
			if (access(tmp->file_names[i], F_OK) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp->file_names[i], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				exit (1);
			}
		}
		i++;
	}
	return (last);
}

void	in_redirection_norm(t_all *tmp, int last_in)
{
	DIR	*dir;
	int	fd;

	dir = opendir(tmp->file_names[last_in]);
	if (dir != NULL)
	{
		ft_putstr_fd("cat: stdin: Is a directory\n", 2);
		closedir(dir);
		exit (1);
	}
	fd = open(tmp->file_names[last_in], O_RDWR, 0644);
	if (fd == -1)
		exit (1);
	dup2(fd, STDIN_FILENO);
	close (fd);
}

void	in_redirect(t_all *all)
{
	t_all	*tmp;
	int		last_in;

	tmp = all;
	if (check_redirct(tmp, REDIR_IN) || check_redirct(tmp, HEREDOC))
	{
		last_in = last_input(tmp);
		if (tmp->file_types[last_in] == REDIR_IN)
			in_redirection_norm(all, last_in);
		else
		{
			dup2(tmp->fd, STDIN_FILENO);
			close (tmp->fd);
		}
	}
	else if (tmp->prev_pip != 0)
		dup2(tmp->prev_pip, STDIN_FILENO);
}
