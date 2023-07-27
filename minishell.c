/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:15:15 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/26 16:48:51 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_struct	g_glo;

int	main(int ac, char **av, char **envp)
{
	t_token	*all;
	t_all	*globy;
	int		tmp;

	if (ac != 1)
		exit (0);
	all = NULL;
	globy = NULL;
	g_glo.exitstatus = 0;
	take_env(envp);
	prompt(&all, &globy, envp);
	tmp = g_glo.exitstatus;
	deallocating_env(&g_glo.env);
	exit (tmp);
	(void)ac;
	(void)av;
}
