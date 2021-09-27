/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 13:39:58 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/26 21:59:37 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_list *tokens)
{
	t_list	*lst;
	int		i;

	lst = tokens;
	while (lst)
	{
		i = -1;
		while (*(((t_command *)lst->vol)->args + ++i) != NULL)
			printf("%s ", *(((t_command *)lst->vol)->args + i));
		printf("\n");
		lst = lst->next;
	}
}

void	print_split(char **str)
{
	int	i;

	i = -1;
	while (*(str + ++i) != NULL)
		printf("%s\n", *(str + i));
}

int	len_split(char **str)
{
	int	i;

	i = 0;
	if (!(str))
		return (i);
	while (*(str + i) != NULL)
		i++;
	return (i);
}
