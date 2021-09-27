/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 15:34:19 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/26 21:52:48 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_of_split(char **str)
{
	int	i;

	i = -1;
	if (!(str))
		return ;
	while (*(str + ++i) != NULL)
	{
		free(*(str + i));
		*(str + i) = NULL;
	}
}

void	free_var(void *var)
{
	if (((t_var *)var)->key)
		free(((t_var *)var)->key);
	if (((t_var *)var)->value)
		free(((t_var *)var)->value);
	if (var)
		free(var);
}

void	free_command(void *command)
{
	if (((t_command *)command)->args)
		free_split_of_split(((t_command *)command)->args);
	free(command);
}

void	free_token(t_list **tokens, char **str, int i)
{
	ft_lstclear(tokens, free_command);
	if (i)
		free_split_of_split(str + i);
	free(str);
	str = NULL;
}
