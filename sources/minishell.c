/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:07:41 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/25 16:33:11 by mmoreira         ###   ########.fr       */
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
	printf("%s\n\n", *line);
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

void	print_tokens(t_list *tokens)
{
	t_list	*lst;
	int		i;

	lst = tokens;
	while (lst)
	{
		i = -1;
		while (*(((t_command *)lst->vol)->args + ++i) != NULL)
			printf("%s ",*(((t_command *)lst->vol)->args + i));
		printf("\n");
		lst = lst->next;
	}
}

static int	split_and_tokenizer(t_list **tokens, char *line)
{
	char	**split;
	int		i;

	i = split_line(&split, line);
	if (i == 1)
	{
		printf("Erro em alocação de memoria\n");
		exit(1);
	}
	if (i == 2)
	{
		free(line);
		return (1);
	}
	i = check_syntax_error(split);
	if (i)
	{
		printf("minishell: syntax error near unexpected token `%s'\n",*(split + i - 1));
		g_shell.status = 2;
		ft_free_split(split);
		free(line);
		return (1);
	}
	*tokens = NULL;
	if (tokenizer(tokens, &split))
	{
		printf("Erro em alocação de memoria\n");
		exit(1);
	}
	print_tokens(*tokens);
	free_token(tokens, split, 0);
	return (0);
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
			continue ;// Linha Vazia
		//------------------------------------

		//Analisar  --------------------------
		if (split_and_tokenizer(&tokens, line))
			continue ;//Linha cheia de espaços
		//------------------------------------

		//Executar  --------------------------
		if (!(ft_strcmp(line, "exit")))
		{
			free(line);
			break ;
		}
		//------------------------------------

		free(line);
		g_shell.status = 0;
	}
}

// rl_on_new_line();
// rl_clear_history();
// rl_replace_line (const char * text, int clear_undo);
// rl_redisplay();
// Pegar a visão das funções do readline / Falar com a lais

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1 && *argv)
		return (1);//Pensar em uma mensagem de erro
	g_shell.varenv = NULL;
	g_shell.status = 0;
	if (set_varenv(envp))
		return (1); //Falha de alocação das varenv
	loop_prompt();
	return (0);
}

//Lembrar de limpar variavel global final