/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:07:52 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/25 15:41:27 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# include<sys/types.h>
# include<sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "./../Libft/libft.h"

typedef struct s_var
{
	int			env;
	char		*key;
	char		*value;
}				t_var;

typedef struct s_command
{
	char		**args;
}				t_command;

typedef struct s_shell
{
	t_list		*varenv;
	int			status;
}				t_shell;

t_shell			g_shell;

//---------------------------------set_varenv-----------------------------------
t_list			*search_var(char *key);
void			delete_var(char *key);
int				insert_var(char *arg, int env);
int				set_varenv(char **envp);
//get_envp

//--------------------------------correct_line----------------------------------
int				on_off_quotes(char *line, int quote1, int quote2, char c);
void			adjust_redirects(char **line);
void			adjust_dollar(char **line);

char			**split_line(char *line);

//-------------------------------free_functions---------------------------------
void			free_split_of_split(char **str);
void			free_var(void *var);
void			free_command(void *command);
void			free_token(t_list **tokens, char **str, int i);

int	tokenizer(t_list **tokens, char ***split);
int	check_syntax_error(char **split);


#endif