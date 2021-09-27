/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:07:41 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/26 22:05:42 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_and_adjust(char **line)
{
	char	*prompt;
	char	buff[4096];

	getcwd(buff, sizeof(buff));
	prompt = ft_strjoin(buff, "$ ");
	*line = readline(prompt);
	free(prompt);
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
	int		i;

	if (split_line(&split, line))
	{
		free(line);
		return (1);
	}
	free(line);
	i = check_syntax_error(split);
	if (i)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
		if (i < 0)
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(*(split + i - 1), 2);
		ft_putendl_fd("'", 2);
		g_shell.status = 2;
		ft_free_split(split);
		return (1);
	}
	*tokens = NULL;
	tokenizer(tokens, &split);
	return (0);
}

void	exec_select(char **args)
{
	char	*command;

	command = *args;
	if (ft_strchr(command, '='))
		insert_var(command, 0);
	else if (is_builtins(command))
		exec_builtins(args);
	else
		exec_no_builtins(args);
}

void	exec_all_commands(t_list *tokens)
{
	t_list	*lst;
	char	**args;

	lst = tokens;
	while (lst)
	{
		args = ((t_command *)lst->vol)->args;
		exec_select(args);
		lst = lst->next;
	}
}

void	loop_prompt(void)
{
	char	*line;
	t_list	*tokens;

	while (1)
	{
		//--Definir os sinais
		//Ler  ------------------------------
		if (read_and_adjust(&line))
			continue ;
		//Analisar  --------------------------
		if (split_and_tokenizer(&tokens, line))
			continue ;
		//Executar  --------------------------
		exec_all_commands(tokens);
		free_token(&tokens, ((t_command *)tokens->vol)->args, 0);
		//------------------------------------
	}
}

// rl_on_new_line();
// rl_clear_history();
// rl_replace_line (const char * text, int clear_undo);
// rl_redisplay();

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
