/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:39:03 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/26 21:53:33 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_b(char **args)
{
	t_list	*lst;

	lst = search_var(*(args + 1));
	if (lst)
		delete_var(*(args + 1));
	g_shell.status = 0;
}
