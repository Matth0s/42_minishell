/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 15:39:11 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/25 15:40:26 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_operator(char *arg)
{
	if (!(ft_strcmp(arg,"|")))
		return (1);
	else if (!(ft_strcmp(arg,"<")) || !(ft_strcmp(arg,">")))
		return (2);
	else if(!(ft_strcmp(arg,"<<")) || !(ft_strcmp(arg,">>")))
		return (3);
	else
		return (0);
}

int	check_syntax_error(char **split)
{
	int		i;

	i = 0;
	if (is_operator(*split))
		return (1) ;
	while(*(split + ++i))
		if (is_operator(*(split + i)) && is_operator(*(split + i - 1)))
			return (i + 1) ;
	if (is_operator(*(split + i - 1)))
		return (i);
	return (0);
}

int	add_command(t_list **tokens, char ** args)
{
	t_command	*command;
	t_list		*lst;

	command = (t_command *)malloc(sizeof(t_command));
	if (!(command))
	{
		free_split_of_split(args);
		return (1);
	}
	command->args = args;
	lst = ft_lstnew(command);
	if (!(lst))
	{
		free_command(command);
		return (1);
	}
	ft_lstadd_back(tokens, lst);
	return (0);

}

int	tokenizer(t_list **tokens, char ***split)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (*(*split + ++i))
	{
		if (is_operator(*(*split + i)) == 1 || !(*(*split + i + 1)))
		{
			if (is_operator(*(*split + i)) == 1)
			{
				free(*(*split + i));
				*(*split + i) = NULL;
			}
			if (add_command(tokens, *split + j))
			{
				free_token(tokens, *split, i + 1);
				return(1);
			}
			j = i + 1;
		}
	}
	return (0);
}
