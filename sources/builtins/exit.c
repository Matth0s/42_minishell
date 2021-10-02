/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:39:23 by mmoreira          #+#    #+#             */
/*   Updated: 2021/10/02 14:13:14 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_b(char **args)
{
	ft_putendl_fd("exit", 2);
	if (args)
	{
		if (ft_splitlen(args) > 1)
		{
			ft_putstr_fd("Minishell: exit: ", 2);
			ft_putstr_fd(*(args + 1), 2);
			ft_putendl_fd(": numeric argument required", 2);
			g_shell.status = 255;
		}
		ft_free_split(args);
	}
	ft_lstclear(&g_shell.varenv, free_var);
	rl_clear_history();
	exit(g_shell.status);
}
