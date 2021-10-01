/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:11:09 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/29 16:07:41 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_b(int fdout)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (buff)
	{
		ft_putendl_fd(buff, fdout);
		g_shell.status = 0;
	}
	else
	{
		ft_putstr_fd("Minishell: pwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_shell.status = errno;
	}
	free(buff);
}
