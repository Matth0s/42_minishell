/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:59:19 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/28 19:01:42 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *arg)
{
	if (!(ft_strcmp(arg, "|")))
		return (1);
	else if (!(ft_strcmp(arg, "<")) || !(ft_strcmp(arg, ">")))
		return (2);
	else if (!(ft_strcmp(arg, "<<")) || !(ft_strcmp(arg, ">>")))
		return (3);
	else
		return (0);
}

int	check_syntax_error1(char **split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (is_operator(*split) == 1)
		j++;
	if (!(j))
		while (*(split + ++i))
			if (is_operator(*(split + i)) && is_operator(*(split + i - 1)))
				break ;
	if (j || i != ft_splitlen(split))
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
		if (j)
			ft_putstr_fd(*split, 2);
		else
			ft_putstr_fd(*(split + i), 2);
		ft_putendl_fd("'", 2);
		g_shell.status = 2;
		return (1);
	}
	return (0);
}

int	check_syntax_error2(char **split)
{
	int	i;

	i = ft_splitlen(split);
	if (is_operator(*(split + i - 1)))
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
		if (is_operator(*(split + i - 1)) == 1)
			ft_putstr_fd("|", 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putendl_fd("'", 2);
		g_shell.status = 2;
		return (1);
	}
	return (0);
}
