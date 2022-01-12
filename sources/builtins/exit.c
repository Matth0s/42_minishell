/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:39:23 by mmoreira          #+#    #+#             */
/*   Updated: 2022/01/12 19:07:41 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	not_a_number(char *str)
{
	int	i;

	i = -1;
	while (*(str + ++i))
		if (!(ft_isdigit(*(str + i))))
			return (1);
	return (0);
}

static int	select_exit_type(char **args)
{
	if (not_a_number(*(args + 1)))
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(*(args + 1), 2);
		ft_putendl_fd(": numeric argument required", 2);
		g_shell.status = 2;
		return (1);
	}
	if (ft_splitlen(args) > 2)
	{
		ft_putendl_fd("Minishell: exit: too many arguments", 2);
		g_shell.status = 1;
		return (0);
	}
	g_shell.status = ft_atoi(*(args + 1));
	return (1);
}

void	exit_b(char **args)
{
	int	ind;

	ft_putendl_fd("exit", 2);
	ind = 1;
	if (args)
	{
		if (ft_splitlen(args) > 1)
			ind = select_exit_type(args);
		if (ind)
			ft_free_split(args);
	}
	if (ind)
	{
		ft_lstclear(&g_shell.varenv, free_var);
		rl_clear_history();
		exit(g_shell.status);
	}
}
