/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:02:43 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/27 01:10:25 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_b(char	**args)
{
	int	i;

	i = ft_splitlen(args);
	if (i == 1)
		ft_putendl_fd("\0", 1);
	else
	{
		if (!(strcmp(*(args + 1), "-n")))
			i = 1;
		else
			i = 0;
		while (*(args + ++i))
		{
			ft_putstr_fd(*(args + i), 1);
			if (*(args + i + 1))
				ft_putstr_fd(" ", 1);
		}
		if (strcmp(*(args + 1), "-n"))
			ft_putendl_fd("\0", 1);
	}
	g_shell.status = 0;
}
