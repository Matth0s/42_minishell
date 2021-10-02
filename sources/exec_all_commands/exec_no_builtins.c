/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:23:46 by mmoreira          #+#    #+#             */
/*   Updated: 2021/10/02 00:45:02 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_standard_fd(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
}

static char	*serach_command(char *path, char *command)
{
	struct stat	buff;
	char		*temp;
	char		*temp2;

	temp2 = ft_strjoin(path, "/");
	temp = ft_strjoin(temp2, command);
	free(temp2);
	if (stat(temp, &buff))
	{
		free(temp);
		temp = NULL;
	}
	return (temp);
}

static char	*find_path_command(char *command)
{
	char		**split;
	char		*temp;
	t_list		*lst;
	int			i;

	lst = search_var("PATH");
	if (!(lst))
		return (NULL);
	split = ft_split(((t_var *)lst->vol)->value, ':');
	i = -1;
	while (*(split + ++i))
	{
		temp = serach_command(*(split + i), command);
		if (temp)
			break ;
	}
	ft_free_split(split);
	return (temp);
}

static int	find_command(char ***args)
{
	char	*command;
	int		i;

	i = 0;
	while (*(**args + i) == '.')
		i++;
	if (*(**args + i) != '/')
	{
		command = find_path_command(**args);
		if (!(command))
		{
			ft_putstr_fd(**args, 2);
			ft_putendl_fd(": command not found", 2);
			g_shell.status = 127;
			return (1);
		}
		free(**args);
		**args = command;
	}
	return (0);
}

void	exec_no_builtins(char **args, int fdin, int fdout)
{
	char	**envp;
	int		status;
	int		pid;

	if (find_command(&args))
		return ;
	get_envp(&envp);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		change_standard_fd(fdin, fdout);
		execve(*args, args, envp);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(*args, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(errno);
	}
	waitpid(pid, &status, 0);
	g_shell.status = WEXITSTATUS(status);
	ft_free_split(envp);
}
