/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redctn_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:38:04 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/25 16:02:31 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	out_redirect(t_all *all)
{
	t_all	*tmp;

	tmp = all;
	if (check_redirct(tmp, REDIR_OUT) || check_redirct(tmp, APPEND))
		dup_last_out(tmp, creat_outfile(tmp));
	else if (tmp->next)
		dup2(tmp->pip[WRIT], STDOUT_FILENO);
}

void	dup_last_out(t_all *tmp, int n)
{
	int	fd;

	if (tmp->file_types[n] == REDIR_OUT)
	{
		fd = open (tmp->file_names[n], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit (1);
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
	else if (tmp->file_types[n] == APPEND)
	{
		fd = open (tmp->file_names[n], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			exit (1);
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
}

void	creat_outfil_norm(t_all *all, int *last, int i)
{
	DIR	*dir;
	int	fd;

	if (all->file_types[i] == REDIR_OUT)
	{
		dir = opendir(all->file_names[i]);
		if (dir != NULL)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(all->file_names[i], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			closedir(dir);
			exit (1);
		}
		fd = open(all->file_names[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit (1);
		close (fd);
		*last = i;
	}
}

void	creat_outfile_sequel(t_all *all, int *last, int i)
{
	int	fd;
	DIR	*dir;

	creat_outfil_norm(all, &(*last), i);
	if (all->file_types[i] == APPEND)
	{
		dir = opendir(all->file_names[i]);
		if (dir != NULL)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(all->file_names[i], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			closedir(dir);
			exit (1);
		}
		fd = open(all->file_names[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			exit (1);
		close (fd);
		*last = i;
	}
}

int	creat_outfile(t_all *all)
{
	int	i;
	int	last;

	i = 0;
	while (all->file_names[i])
	{
		if (all->file_types[i] == REDIR_IN)
		{
			if (access(all->file_names[i], F_OK) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(all->file_names[i], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				exit (1);
			}
		}
		creat_outfile_sequel(all, &last, i);
		i++;
	}
	return (last);
}
