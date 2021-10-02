/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:53:10 by mmoreira          #+#    #+#             */
/*   Updated: 2021/10/02 00:46:25 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_attribution(char *var, int *status)
{
	if (*var == '=')
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*status = 1;
	}
	else
		insert_var(var, 1);
}

static void	set_new_env(char *key)
{
	t_list	*lst;

	lst = search_var(key);
	if (lst)
	{
		((t_var *)lst->vol)->env = 1;
		g_shell.numenv++;
	}
}

void	export_b(char **args, int fdout)
{
	int		status;
	int		i;

	status = 0;
	i = ft_splitlen(args);
	if (i == 1)
		env_b(1, fdout);
	else
	{
		i = 0;
		while (*(args + ++i))
		{
			if (ft_strchr(*(args + i), '='))
				set_attribution(*(args + i), &status);
			else
				set_new_env(*(args + i));
		}
	}
	g_shell.status = status;
}
