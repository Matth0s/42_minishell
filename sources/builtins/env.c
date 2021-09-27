/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:56:01 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/26 21:54:16 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_b(void)
{
	t_list	*lst;
	t_var	*var;

	lst = g_shell.varenv;
	while (lst)
	{
		var = (t_var *)lst->vol;
		if (var->env)
		{
			ft_putstr_fd(var->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(var->value, 1);
		}
		lst = lst->next;
	}
	g_shell.status = 0;
}
