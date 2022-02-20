/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:56:01 by mmoreira          #+#    #+#             */
/*   Updated: 2022/02/19 13:39:40 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_b(int fdout)
{
	t_list	*lst;
	t_var	*var;

	lst = g_shell.varenv;
	while (lst)
	{
		var = (t_var *)lst->vol;
		if (var->env)
		{
			ft_putstr_fd(var->key, fdout);
			ft_putstr_fd("=", fdout);
			ft_putendl_fd(var->value, fdout);
		}
		lst = lst->next;
	}
	g_shell.status = 0;
}
