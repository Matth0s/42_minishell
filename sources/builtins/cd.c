/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 13:30:24 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/29 16:05:24 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_vars_pwd(void)
{
	char	buff[4096];
	char	*temp;
	t_list	*lst1;
	t_list	*lst2;

	lst1 = search_var("PWD");
	if (lst1)
		temp = ft_strjoin("OLDPWD=", ((t_var *)lst1->vol)->value);
	else
		temp = ft_strjoin("OLDPWD=", "\0");
	lst2 = search_var("OLDPWD");
	if (lst2 && ((t_var *)lst2->vol)->env)
		insert_var(temp, 1);
	else
		insert_var(temp, 0);
	free(temp);
	getcwd(buff, sizeof(buff));
	temp = ft_strjoin("PWD=", buff);
	if (lst1 && ((t_var *)lst1->vol)->env)
		insert_var(temp, 1);
	else
		insert_var(temp, 0);
	free(temp);
}

static int	go_to_dir(char *dir)
{
	int	i;

	i = chdir(dir);
	if (i)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	set_vars_pwd();
	return (0);
}

static int	go_to_varenv(char *var, int ind)
{
	t_list	*lst;

	lst = search_var(var);
	if (lst)
	{
		if (*((t_var *)lst->vol)->value != '\0')
			return (go_to_dir(((t_var *)lst->vol)->value));
	}
	if (ind)
		return (go_to_dir("/"));
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd(" not set", 2);
	return (1);
}

void	cd_b(char **args, int fdout)
{
	int	i;

	i = ft_splitlen(args);
	if (i > 2)
	{
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
		g_shell.status = 1;
	}
	else if (i == 1)
		g_shell.status = go_to_varenv("HOME", 0);
	else
	{
		if (!(strcmp(*(args + 1), "~")))
			g_shell.status = go_to_varenv("HOME", 1);
		else if (!(strcmp(*(args + 1), "-")))
		{
			g_shell.status = go_to_varenv("OLDPWD", 0);
			if (!(g_shell.status))
				pwd_b(fdout);
		}
		else
			g_shell.status = go_to_dir(*(args + 1));
	}
}
