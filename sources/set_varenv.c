/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_varenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:32:28 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/22 02:05:24 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_var(void *var)
{
	if (((t_var *)var)->key)
		free(((t_var *)var)->key);
	if (((t_var *)var)->value)
		free(((t_var *)var)->value);
	if (var)
		free(var);
}

static int	get_varenv(t_list **env, char *arg)
{
	t_list	*lst;
	t_var	*var;
	char	*sep;

	var = (t_var *)malloc(sizeof(t_var));
	if (!(var))
		return (1);
	sep = ft_strchr(arg, '=');
	var->key = ft_substr(arg, 0, sep - arg);
	var->value = ft_strdup(sep + 1);
	lst = ft_lstnew(var);
	if (!(var->key) || !(var->value) || !(lst))
	{
		free_var(var);
		return (1);
	}
	ft_lstadd_back(env, lst);
	return (0);
}

int	set_varenv(char **envp)
{
	int		i;

	i = -1;
	while (*(envp + ++i))
	{
		if (get_varenv(&g_shell.env, *(envp + i)))
		{
			ft_lstclear(&g_shell.env, free_var);
			return (1);
		}
	}
	return (0);
}
