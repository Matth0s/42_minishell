/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 01:50:38 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/23 02:10:36 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	on_off_quotes(char *line, int quote1, int quote2, char c)
{
	if (quote2 == -1)
	{
		if (quote1 == -1 && ft_strchr(line + 1, c))
			return (-1);
		else if (quote1 == 1)
			return (-1);
	}
	return (1);
}

static void	insert_spaces(char **line, int *i, int ind)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(*line, 0, *i);
	if (*i)
		if (*(*(line) + *i - 1) != ' ')
			temp = ft_addchar(temp, ' ');
	temp = ft_addchar(temp, *(*(line) + *i));
	if (ind)
		temp = ft_addchar(temp, *(*(line) + (*i)++));
	if (*(*(line) + *i + 1) != ' ')
		temp = ft_addchar(temp, ' ');
	temp2 = ft_strjoin(temp, *(line) + *i + 1);
	free(temp);
	free(*line);
	*line = temp2;
	(*i)++;
}

static void	check_spaces(char **line, int *i)
{
	if (*(*line + *i) == '|')
		insert_spaces(line, i, 0);
	if (*(*line + *i) == '>')
	{
		if (*(*line + *i + 1) == '>')
			insert_spaces(line, i, 1);
		else
			insert_spaces(line, i, 0);
	}
	if (*(*line + *i) == '<')
	{
		if (*(*line + *i + 1) == '<')
			insert_spaces(line, i, 1);
		else
			insert_spaces(line, i, 0);
	}
}

void	adjust_redirects(char **line)
{
	int		db_quote;
	int		sp_quote;
	int		i;

	i = -1;
	sp_quote = -1;
	db_quote = -1;
	while (*(*line + ++i))
	{
		if (*(*line + i) == '\'')
			sp_quote *= on_off_quotes((*line + i), sp_quote, db_quote, '\'');
		if (*(*line + i) == '\"')
			db_quote *= on_off_quotes((*line + i), db_quote, sp_quote, '\"');
		if (sp_quote == -1 && db_quote == -1)
			check_spaces(line, &i);
	}
}
