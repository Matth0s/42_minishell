/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 01:50:38 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/22 17:08:18 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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

void	remove_dollar(char **line, int *i)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(*line, 0, *i);
	temp2 =ft_strdup(*line + *i + 1);
	free(*line);
	*line = ft_strjoin(temp,temp2);
	free(temp);
	free(temp2);
	(*i)--;
}
//------------------------------------------------------------------------------
/* void	insert_var()

void	search_var()

void	delete_var() */
//------------------------------------------------------------------------------
/* void	replace_dollar(char *line, int *i, int ind)
{

}
 */
void	check_dollar(char **line, int *i, int quote)
{
	if (*(*line + *i + 1) == '\"')
	{
		if (quote == -1 && ft_strchr((*line + *i + 2), '\"'))
			remove_dollar(line, i);
		else if (quote == -1 && !(ft_strchr((*line + *i + 2), '\"')))
			printf("decidir o que fazer\n");
		if (quote == 1)
			return ;
	}
	else if (*(*line + *i + 1) == '\'')
	{
		if (ft_strchr((*line + *i + 2), '\''))
			remove_dollar(line, i);
		else
			printf("decidir o que fazer\n");
	}
	else if (*(*line + *i + 1) == '$')
	{
		(*i)++;
		printf("decidir o que fazer\n");
	}
	else if (*(*line + *i + 1) == ' ' || *(*line + *i + 1) == '=')
		return ;
	else
		printf("subistituir valor variavel\n");//Parar de ler o dolar em = oi ' '
		//caso não tenha some dolar e a string
}


void	correct_line(char **line)
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
		if (*(*line + i) == '$' && sp_quote == -1)
			check_dollar(line, &i, db_quote);
	}
}
