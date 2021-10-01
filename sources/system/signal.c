/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 00:54:12 by mmoreira          #+#    #+#             */
/*   Updated: 2021/10/01 19:39:44 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler_in_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		exit(130);
	}
}

void	sighandler_in_execution(int sig)
{
	if (sig == SIGINT)
	{
		g_shell.status = 130;
		ft_putchar_fd('\n', 1);
	}
	if (sig == SIGQUIT)
	{
		g_shell.status = 131;
		ft_putendl_fd("Quit (core dumped)", 2);
	}
}

void	sighandler_in_prompt(int sig)
{
	if (sig == SIGINT)
	{
		g_shell.status = 130;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_sigaction(struct sigaction *newact, void (*handler)(int))
{
	newact->sa_handler = handler;
	newact->sa_flags = 0;
	sigemptyset(&newact->sa_mask);
	sigaction(SIGINT, newact, NULL);
	sigaction(SIGQUIT, newact, NULL);
}
