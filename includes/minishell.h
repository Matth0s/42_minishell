/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:07:52 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/27 00:57:21 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../Libft/libft.h"
# include <errno.h>

# include <sys/types.h>
# include <sys/stat.h>

# include <sys/wait.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

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
	int			numenv;
	t_list		*varenv;
	int			status;
}				t_shell;

t_shell			g_shell;

//---------------------------------set_varenv-----------------------------------
t_list			*search_var(char *key);
void			delete_var(char *key);
int				insert_var(char *arg, int env);
int				set_varenv(char **envp);
int				get_envp(char ***envp);

//------------------------------read_and_adjust---------------------------------
int				on_off_quotes(char *line, int quote1, int quote2, char c);
void			adjust_redirects(char **line);
void			adjust_dollar(char **line);

//---------------------------------tokenizer------------------------------------
int				is_operator(char *arg);
int				split_line(char ***split, char *line);
int				check_syntax_error(char **split);
int				tokenizer(t_list **tokens, char ***split);

//-------------------------------exec_functions----------------------------------

//------------------------------exec_no_builtins--------------------------------
char			*find_path_command(char *command);
int				find_command(char ***args);
void			exec_no_builtins(char **args);

//-------------------------------exec_builtins----------------------------------
int				is_builtins(char *command);
void			exec_builtins(char **args);

//----------------------------------builtins------------------------------------
void			echo_b(char **args);
void			cd_b(char **args);
void			pwd_b(void);
void			export_b(char **args);
void			unset_b(char **args);
void			env_b(void);
void			exit_b(char **args);

//-----------------------------------signal-------------------------------------
//				futuramente sighandler_in_exec
void			sighandler_in_prompt(int sig);
void			set_sigaction(struct sigaction *newact, void (*handler)(int));

//-------------------------------free_functions---------------------------------
void			free_split_of_split(char **str);
void			free_var(void *var);
void			free_command(void *command);
void			free_token(t_list **tokens, char **str, int i);



#endif