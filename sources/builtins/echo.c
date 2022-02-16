/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:02:43 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/29 16:06:18 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_b(char	**args, int fdout)
{
	int	i;

	i = ft_splitlen(args);
	if (i == 1)
		ft_putendl_fd("\0", fdout);
	else
	{
		if (!(ft_strcmp(*(args + 1), "-n")))
			i = 1;
		else
			i = 0;
		while (*(args + ++i))
		{
			ft_putstr_fd(*(args + i), fdout);
			if (*(args + i + 1))
				ft_putstr_fd(" ", fdout);
		}
		if (ft_strcmp(*(args + 1), "-n"))
			ft_putendl_fd("\0", fdout);
	}
	g_shell.status = 0;
}
