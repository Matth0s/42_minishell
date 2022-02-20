/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:53:10 by mmoreira          #+#    #+#             */
/*   Updated: 2022/02/19 15:03:17 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char **str, int i, int j)
{
	char	*temp;

	temp = *(str + i);
	*(str + i) = *(str + j);
	*(str + j) = temp;
}

static void	sort_envs(char **str, int start, int end)
{
	int		i;
	int		j;

	if (end - start < 2)
		return ;
	i = start + 1;
	j = start + 1;
	while (j < end)
	{
		if (ft_strcmp(*(str + start), *(str + i)) < 0)
		{
			while (j < end && ft_strcmp(*(str + start), *(str + j)) < 0)
				j++;
			if (j == end)
				break ;
			swap(str, i, j);
		}
		i++;
		j++;
	}
	swap(str, start, i - 1);
	sort_envs(str, start, i - 1);
	sort_envs(str, i, end);
}

static void	set_new_env(char *var, int *status)
{
	t_list	*lst;

	if (ft_strchr(var, '='))
	{
		if (*var == '='
			|| (ft_strchr(var, '\"')) || (ft_strchr(var, '\'')))
		{
			ft_putstr_fd("Minishell: export: `", 2);
			ft_putstr_fd(var, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			*status = 1;
		}
		else
			insert_var(var, 1);
	}
	else
	{
		lst = search_var(var);
		if (lst)
		{
			((t_var *)lst->vol)->env = 1;
			g_shell.numenv++;
		}
	}
}

void	export_b(char **args, int fdout)
{
	int		status;
	char	**envp;
	int		i;

	status = 0;
	i = ft_splitlen(args);
	if (i == 1)
	{
		get_envp(&envp);
		sort_envs(envp, 0, ft_splitlen(envp));
		i = -1;
		while (*(envp + ++i))
		{
			ft_putstr_fd("declare -x ", fdout);
			ft_putendl_fd(*(envp + i), fdout);
		}
		ft_free_split(envp);
	}
	else
	{
		i = 0;
		while (*(args + ++i))
			set_new_env(*(args + i), &status);
	}
	g_shell.status = status;
}
