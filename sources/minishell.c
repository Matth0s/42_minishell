/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:07:41 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/25 15:57:31 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_and_adjust(char **line)
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

void	loop_prompt(void)
{
	char	*line;
	char	**split;
	t_list	*tokens;
	t_list	*cmd;
	int		i;

	while (1)
	{
		//--Definir os sinais

		//Ler  ------------------------------
		if (read_and_adjust(&line))
			continue ;// Linha Vazia
		//------------------------------------

		//Analisar  --------------------------
		split = split_line(line);
		if (!(split))
		{
			free(line);
			continue ; //Pode ser erro de malloc ou linha só com espaços
		}
		i = check_syntax_error(split);
		if (i)
		{

			printf("minishell: syntax error near unexpected token `%s'\n",*(split + i - 1));
			g_shell.status = 2;
			ft_free_split(split);
			free(line);
			continue ; //Erro de sintax
		}
		tokens = NULL;
 		if (tokenizer(&tokens, &split))
		{
			free(line);
			continue ; //Erro de malloc
		}
		cmd = tokens;
		while (cmd)
		{
			i = -1;
			while (*(((t_command *)cmd->vol)->args + ++i) != NULL)
				printf("%s ",*(((t_command *)cmd->vol)->args + i));
			printf("\n");
			cmd = cmd->next;
		}
		free_token(&tokens, split, 0);
		printf("%s\n", line);
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

/* 	rl_on_new_line();
	rl_clear_history();
	rl_replace_line (const char * text, int clear_undo);
	rl_redisplay(); */
	//Pegar a visão das funções do readline / Falar com a lais

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1 && *argv)
		return (0);//Pensar em uma mensagem de erro
	g_shell.varenv = NULL;
	g_shell.status = 0;
	if (set_varenv(envp))
		return (0); //Falha de alocação das varenv
	loop_prompt();
	return (0);
}

//Lembrar de limpar variavel global final