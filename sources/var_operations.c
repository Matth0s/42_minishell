/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:32:28 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/25 15:35:21 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*search_var(char *key)
{
	t_list	*lst;
	t_var	*var;

	lst = g_shell.varenv;
	while (lst)
	{
		var = (t_var *)lst->vol;
		if (!(ft_strcmp(var->key, key)))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	delete_var(char *key)
{
	t_list	*lst;
	t_list	*prev;
	t_list	*next;

	lst = search_var(key);
	if (!(lst))
		return ;
	prev = lst->prev;
	next = lst->next;
	prev->next = next;
	next->prev = prev;
	ft_lstclear(&lst, free_var);
}

int	insert_var(char *arg, int env)
{
	t_list	*lst;
	t_var	*var;
	char	*sep;

	var = (t_var *)malloc(sizeof(t_var));
	if (!(var))
		return (1);
	sep = ft_strchr(arg, '=');
	var->env = env;
	var->key = ft_substr(arg, 0, sep - arg);
	var->value = ft_strdup(sep + 1);
	lst = ft_lstnew(var);
	if (!(var->key) || !(var->value) || !(lst))
	{
		free_var(var);
		return (1);
	}
	delete_var(var->key);
	ft_lstadd_back(&g_shell.varenv, lst);
	return (0);
}

int	set_varenv(char **envp)
{
	int		i;

	i = -1;
	while (*(envp + ++i))
	{
		if (insert_var(*(envp + i), 1))
		{
			ft_lstclear(&g_shell.varenv, free_var);
			return (1);
		}
	}
	return (0);
}
