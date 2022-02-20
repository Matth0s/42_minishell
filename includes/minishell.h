/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:07:52 by mmoreira          #+#    #+#             */
/*   Updated: 2022/02/20 14:07:57 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../Libft/libft.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <sys/wait.h>
# include <errno.h>
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

//----------------------------split_and_tokenizer-------------------------------
int				is_operator(char *arg);
int				split_line(char ***split, char *line);
int				check_syntax_error1(char **split);
int				check_syntax_error2(char **split);
int				tokenizer(t_list **tokens, char ***split);

//-----------------------------exec_all_commands--------------------------------
void			create_pipe(t_list *lst, int (*fd)[], int *fdin, int *fdout);
char			**set_fds_and_args(char **split, int *fdin, int *fdout);
int				set_heredoc(char *eof, int *fd);
void			select_exec(char **args, int ind, int fdin, int fdout);
int				is_builtins(char *command);
void			exec_builtins(char **args, int ind, int fdout);
void			exec_no_builtins(char **args, int fdin, int fdout);

//----------------------------------builtins------------------------------------
void			echo_b(char **args, int fdout);
void			cd_b(char **args, int fdout);
void			pwd_b(int fdout);
void			export_b(char **args, int fdout);
void			unset_b(char **args);
void			env_b(int fdout);
void			exit_b(char **args);

//-----------------------------------signal-------------------------------------
void			sighandler_in_heredoc(int sig);
void			sighandler_in_execution(int sig);
void			sighandler_in_prompt(int sig);
void			set_sigaction(struct sigaction *newact, void (*handler)(int),
					int sig);

//-------------------------------free_functions---------------------------------
void			free_split_of_split(char **str);
void			free_var(void *var);
void			free_command(void *command);
void			free_token(t_list **tokens, char **str, int i);

#endif