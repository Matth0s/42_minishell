/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_and_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:35:30 by mmoreira          #+#    #+#             */
/*   Updated: 2021/10/01 16:53:23 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc(char *eof, int fd)
{
	struct sigaction	newact;
	char				*line;

	set_sigaction(&newact, sighandler_in_heredoc);
	while (1)
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

static void	open_heredoc(char *eof, int *fd)
{
	struct sigaction	newact;
	int					status;
	int					pid;

	set_sigaction(&newact, SIG_IGN);
	if (open_fd(NULL, O_WRONLY | O_CREAT | O_TRUNC, 0, fd))
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		write_heredoc(eof, *fd);
	waitpid(pid, &status, 0);
	g_shell.status = WEXITSTATUS(status);
	if (g_shell.status)
		*fd = -1;
	else
	{
		open_fd(NULL, O_RDONLY, 0, fd);
		unlink("/tmp/here_document_minishell.tmp");
	}
}

static void	create_fds(char **split, int *fdin, int *fdout)
{
	if (!(strcmp(*split, ">")))
		open_fd(*(split + 1), O_WRONLY | O_CREAT | O_TRUNC, 1, fdout);
	else if (!(strcmp(*split, "<")))
		open_fd(*(split + 1), O_RDONLY | O_CREAT, 0, fdin);
	else if (!(strcmp(*split, ">>")))
		open_fd(*(split + 1), O_WRONLY | O_CREAT | O_APPEND, 1, fdout);
	else
		open_heredoc(*(split + 1), fdin);
}

static int	create_args(char ***temp, char **split)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (*(split + ++i))
		if (is_operator(*(split + i)))
			j++;
	i = ft_splitlen(split) - j * 2;
	*temp = malloc((i + 1) * sizeof(char *));
	if (!(*temp))
		return (1);
	*(*temp + i) = NULL;
	return (0);
}

char	**set_std_and_args(char **split, int *fdin, int *fdout)
{
	char	**temp;
	int		i;
	int		j;

	j = 0;
	i = -1;
	if (create_args(&temp, split))
		return (NULL);
	while (*(split + ++i))
	{
		if (is_operator(*(split + i)))
		{
			if (*fdin != -1)
				create_fds(split + i, fdin, fdout);
			i++;
		}
		else
		{
			*(temp + j) = ft_strdup(*(split + i));
			j++;
		}
	}
	if (*fdin == -1)
		ft_free_split(temp);
	return (temp);
}
