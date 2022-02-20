/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:22:46 by mmoreira          #+#    #+#             */
/*   Updated: 2022/02/20 13:49:46 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_list *lst, int (*fd)[], int *fdin, int *fdout)
{
	if (lst->prev)
		*fdin = (*fd)[0];
	else
		*fdin = dup(0);
	if (lst->next)
	{
		if (pipe(*fd) < 0)
		{
			ft_putstr_fd("Minishell: pipe fail: ", 2);
			ft_putendl_fd(strerror(errno), 2);
			*fdout = dup(1);
			(*fd)[0] = 0;
		}
		else
			*fdout = (*fd)[1];
	}
	else
		*fdout = dup(1);
}

static int	exec_atribuation(char **args, int ind)
{
	int	i;

	i = 0;
	while (*(args + i))
	{
		if (!(ft_strchr(*(args + i), '=')) || *(*(args + i)) == '='
			|| (ft_strchr(*(args + i), '\"')) || (ft_strchr(*(args + i), '\'')))
			break ;
		i++;
	}
	if (i == ft_splitlen(args) && !(ind))
	{
		i = -1;
		while (*(args + ++i))
			insert_var(*(args + i), 0);
	}
	return (i);
}

void	select_exec(char **args, int ind, int fdin, int fdout)
{
	struct sigaction	newact;
	int					equals;

	if (args && *args)
	{
		equals = 0;
		set_sigaction(&newact, sighandler_in_execution, SIGINT);
		set_sigaction(&newact, sighandler_in_execution, SIGQUIT);
		if (ft_strchr(*args, '=') && **args != '=')
			equals = exec_atribuation(args, ind);
		if (equals != ft_splitlen(args))
		{
			if (is_builtins(*(args + equals)))
				exec_builtins(args + equals, ind, fdout);
			else
				exec_no_builtins(args + equals, fdin, fdout);
		}
	}
	if (args)
		ft_free_split(args);
}
