/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:07:41 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/28 02:27:49 by mmoreira         ###   ########.fr       */
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
	prompt_green = ft_strjoin("\001\033[1;30m\002", buff);//mudar para 36
	prompt_reset = ft_strjoin("\001\033[0;0m\002", "$ ");
	prompt_full = ft_strjoin(prompt_green, prompt_reset);
	*line = readline(prompt_full);
	free(prompt_green);
	free(prompt_reset);
	free(prompt_full);
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



void	exec_atribuation(char **args, int ind)
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
		exec_select(args + i, ind);
}

void	exec_select(char **args, int ind)
{
	char	*command;

	command = *args;
	if (ft_strchr(command, '=') && *command != '=')
		exec_atribuation(args, ind);
	else if (is_builtins(command))
		exec_builtins(args, ind);
	else
		exec_no_builtins(args);
}

void	exec_all_commands(t_list *tokens)
{
	t_list	*lst;
	char	**args;
	int		ind;
	struct sigaction	newact;

	lst = tokens;
	ind = ft_lstsize(lst);
	while (lst)
	{
		set_sigaction(&newact, sighandler_in_execution);
		args = ((t_command *)lst->vol)->args;
		exec_select(args, ind - 1);
		lst = lst->next;
	}
}


void	loop_prompt(void)
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
		free_token(&tokens, ((t_command *)tokens->vol)->args, 0);
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
