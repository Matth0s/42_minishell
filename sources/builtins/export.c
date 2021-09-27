/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:53:10 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/26 21:53:41 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_b(char **args)
{
	t_list	*lst;

	lst = search_var(*(args + 1));
	if (lst)
		((t_var *)lst->vol)->env = 1;
	g_shell.status = 0;
}
