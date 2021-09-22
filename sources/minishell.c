/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:07:41 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/22 16:28:07 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_prompt(void)
{
	char	*prompt;
	char	*buff;
	char	*pwd;

	buff = NULL;
	pwd = getcwd(buff, 0);
	prompt = ft_strjoin(pwd, "$ ");
	free(pwd);
	free(buff);
	return (prompt);
}

void	loop_prompt(void)
{
	char	*prompt;
	char	*line;

	while (1)
	{
		//--Definir os sinais
		//Ler
		prompt = make_prompt();
		line = readline(prompt);
		free(prompt);
		if (line && *line)
			add_history(line);
		//Analisar
		correct_line(&line);
		printf("%s\n", line);
		//Executar
		if (!(ft_strncmp(line, "exit", ft_strlen(line))) && *line != '\0')
		{
			free(line);
			break ;
		}
		free(line);
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
	g_shell.env = NULL;
	g_shell.local = NULL;
	if (set_varenv(envp))
		return (0); //Falha de alocação
	loop_prompt();
	return (0);
}
//Lembrar de limpar variavel global final