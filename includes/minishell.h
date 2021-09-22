/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:07:52 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/22 01:57:22 by mmoreira         ###   ########.fr       */
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
	char		*key;
	char		*value;
}				t_var;

typedef struct s_shell
{
	t_list		*env;
	t_list		*local;
}				t_shell;

t_shell			g_shell;

//---------------------------------set_varenv-----------------------------------
void			free_var(void *var);
int				set_varenv(char **envp);

//--------------------------------correct_line----------------------------------
void			correct_line(char **line);

#endif