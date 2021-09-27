/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 13:17:29 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/26 20:07:12 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(char *command)
{
	if (!(ft_strcmp(command, "echo"))
		|| !(ft_strcmp(command, "cd"))
		|| !(ft_strcmp(command, "pwd"))
		|| !(ft_strcmp(command, "export"))
		|| !(ft_strcmp(command, "unset"))
		|| !(ft_strcmp(command, "env"))
		|| !(ft_strcmp(command, "exit")))
		return (1);
	return (0);
}

void	exec_builtins(char **args)
{
	if ((!(ft_strcmp(*args, "echo"))))
		echo_b(args);
	else if (!(ft_strcmp(*args, "cd")))
		cd_b(args);
	else if (!(ft_strcmp(*args, "pwd")))
		pwd_b();
	else if (!(ft_strcmp(*args, "export")))
		export_b(args);
	else if (!(ft_strcmp(*args, "unset")))
		unset_b(args);
	else if (!(ft_strcmp(*args, "env")))
		env_b();
	else
		exit_b(args);
}
