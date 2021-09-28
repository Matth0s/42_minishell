/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:39:03 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/28 01:45:13 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_b(char **args)
{
	int		status;
	int		i;

	i = 0;
	status = 0;
	while (*(args + ++i))
	{
		if (ft_strchr(*(args + i), '='))
		{
			ft_putstr_fd("Minishell: unset: `", 2);
			ft_putstr_fd(*(args + i), 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
			delete_var(*(args + i));
	}
	g_shell.status = status;
}
