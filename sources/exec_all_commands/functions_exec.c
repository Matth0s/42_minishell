/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:22:46 by mmoreira          #+#    #+#             */
/*   Updated: 2021/10/01 16:18:50 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_fd(char *name, int flags, int direct, int *fd)
{
	if (*fd != 0 && *fd != 1)
		close(*fd);
	if (name)
		*fd = open(name, flags, 0777);
	else
	{
		*fd = open("/tmp/here_document_minishell.tmp", flags, 0777);
		name = "<<";
	}
	if (*fd < 0)
	{
		ft_putstr_fd("Minishell: redirect fail: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		*fd = dup(direct);
		return (1);
	}
	return (0);
}

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

void	exec_atribuation(char **args, int ind, int fdin, int fdout)
{
	int	i;

	i = 0;
	while (*(args + ++i))
		if (!(ft_strchr(*(args + i), '=')) || *(*(args + i)) == '=')
			break ;
	if (i == ft_splitlen(args))
	{
		i = -1;
		while (*(args + ++i))
			insert_var(*(args + i), 0);
	}
	else
		select_exec(args + i, ind, fdin, fdout);
}

void	select_exec(char **args, int ind, int fdin, int fdout)
{
	struct sigaction	newact;
	char				*command;

	if (args && *args)
	{
		command = *args;
		set_sigaction(&newact, sighandler_in_execution);
		if (ft_strchr(command, '=') && *command != '=')
			exec_atribuation(args, ind, fdin, fdout);
		else if (is_builtins(command))
			exec_builtins(args, ind, fdout);
		else
			exec_no_builtins(args, fdin, fdout);
	}
	if (args)
		ft_free_split(args);
}
