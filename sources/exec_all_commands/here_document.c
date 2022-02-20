/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:12:00 by mmoreira          #+#    #+#             */
/*   Updated: 2022/02/20 14:24:02 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_heredoc(int *fd)
{
	ft_putstr_fd("Minishell: here_document error: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	*fd = dup(0);
	return (1);
}

static void	write_heredoc(char *eof, int fd)
{
	struct sigaction	newact;
	char				*line;

	set_sigaction(&newact, sighandler_in_heredoc, SIGINT);
	while (42)
	{
		line = readline("> ");
		if (!(line))
		{
			ft_putstr_fd("Minishell: warning: here-document delimited", 2);
			ft_putstr_fd(" by end-of-file (wanted `", 2);
			ft_putstr_fd(eof, 2);
			ft_putendl_fd("')", 2);
			break ;
		}
		if (!(ft_strcmp(line, eof)))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	exit(0);
}

static int	open_heredoc(int *fd, int flags)
{
	*fd = open("/tmp/here_document_minishell.tmp", flags, 0777);
	if (*fd < 0)
		return (error_heredoc(fd));
	return (0);
}

int	set_heredoc(char *eof, int *fd)
{
	struct sigaction	newact;
	int					status;
	int					pid;

	set_sigaction(&newact, SIG_IGN, SIGINT);
	set_sigaction(&newact, SIG_IGN, SIGQUIT);
	if (open_heredoc(fd, O_WRONLY | O_CREAT | O_TRUNC))
		return (0);
	pid = fork();
	if (pid < 0)
		return (error_heredoc(fd) - 1);
	if (pid == 0)
		write_heredoc(eof, *fd);
	waitpid(pid, &status, 0);
	g_shell.status = WEXITSTATUS(status);
	if (g_shell.status)
		*fd = -1;
	else
	{
		if (open_heredoc(fd, O_RDONLY))
			return (0);
		unlink("/tmp/here_document_minishell.tmp");
	}
	return (0);
}
