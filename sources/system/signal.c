/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 00:54:12 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/28 02:27:05 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler_in_execution(int sig)
{
	if (sig == SIGINT)
	{
		g_shell.status = 130;
		ft_putchar_fd('\n', 1);
	}
	//Falta implementar ^D
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
	if (sig == SIGQUIT)
	{
		//Falta implementar ^D
	}
}

// testar ^C em propt vazio e ver se dar newline vazia
// testar ^\ e ver se não da nada em prompt vazio
// testar ^D em linha vazia sai do minishell

// testar ^C depois de escrever alguma coisa e ver se da nova linha de comando
// teste ^D com linha escrita e ver se não da nada
// testar ^\ em linha escrita e ver se não da nada

void	set_sigaction(struct sigaction *newact, void (*handler)(int))
{
	newact->sa_handler = handler;
	newact->sa_flags = 0;

	sigemptyset(&newact->sa_mask);
	sigaction(SIGINT, newact, NULL);
	sigaction(SIGQUIT, newact, NULL);
}
