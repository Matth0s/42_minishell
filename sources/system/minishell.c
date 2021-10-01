/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:07:41 by mmoreira          #+#    #+#             */
/*   Updated: 2021/10/01 15:52:44 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_and_adjust(char **line)
{
	char	buff[4096];
	char	*prompt_green;
	char	*prompt_reset;
	char	*prompt_full;

	getcwd(buff, sizeof(buff));
	prompt_green = ft_strjoin("\001\033[1;36m\002", buff);
	prompt_reset = ft_strjoin("\001\033[0;0m\002", "$ ");
	prompt_full = ft_strjoin(prompt_green, prompt_reset);
	*line = readline(prompt_full);
	free(prompt_green);
	free(prompt_reset);
	free(prompt_full);
	if (!(*line))
		return (1);
	if (!(*(*line)))
	{
		free(*line);
		return (1);
	}
	add_history(*line);
	adjust_redirects(line);
	adjust_dollar(line);
	return (0);
}

static int	split_and_tokenizer(t_list **tokens, char *line)
{
	char	**split;


	if (split_line(&split, line))
	{
		free(line);
		return (1);
	}
	free(line);
	if (check_syntax_error1(split) || check_syntax_error2(split))
	{
		ft_free_split(split);
		return (1);
	}
	*tokens = NULL;
	tokenizer(tokens, &split);
	return (0);
}

static void	exec_all_commands(t_list *tokens)
{
	t_list	*lst;
	char	**args;
	int		fd_pipe[2];
	int		fd_loop[2];
	int		ind;

	lst = tokens;
	ind = ft_lstsize(lst);
	while (lst)
	{
		create_pipe(lst, &fd_pipe, &fd_loop[0], &fd_loop[1]);
		args = ((t_command *)lst->vol)->args;
		args = set_std_and_args(args, &fd_loop[0], &fd_loop[1]);
		if (fd_loop[0] == -1)
		{
			close(fd_pipe[0]);
			close(fd_loop[1]);
			break;
		}
		exec_select(args, ind - 1, fd_loop[0], fd_loop[1]);
		close(fd_loop[0]);
		close(fd_loop[1]);
		lst = lst->next;
	}
	free_token(&tokens, ((t_command *)tokens->vol)->args, 0);
}

static void	loop_prompt(void)
{
	struct sigaction	newact;
	char				*line;
	t_list				*tokens;

	while (1)
	{
		//Definir os sinais------------------
		set_sigaction(&newact, sighandler_in_prompt);

		//Ler  ------------------------------
		if (read_and_adjust(&line))
			continue ;

		//Analisar  --------------------------
		if (split_and_tokenizer(&tokens, line))
			continue ;

		//Executar  --------------------------
		if (!(ft_strcmp(((t_command *)tokens->vol)->args[0], "exit")))
		{
			free_token(&tokens, ((t_command *)tokens->vol)->args, 0);
			break ;
		}
		exec_all_commands(tokens);
		//------------------------------------
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1 && *argv)
	{
		ft_putendl_fd("Minishell: Too many arguments", 1);
		return (1);
	}
	g_shell.numenv = 0;
	g_shell.varenv = NULL;
	g_shell.status = 0;
	if (set_varenv(envp))
	{
		ft_putendl_fd("Minishell: Error of alloc variable of environments", 1);
		return (1);
	}
	loop_prompt();
	return (0);
}
