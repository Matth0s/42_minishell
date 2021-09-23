/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 01:50:38 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/23 00:49:04 by mmoreira         ###   ########.fr       */
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

static void	correct_redirects(char **line)
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
//------------------------------------------------------------------------------
//char	*ft_multi_strjoin(int len, ...)

void	replace_dollar(char **line, int *i, int quote)
{
	t_list	*lst;
	char	*temp;
	char	*temp2;
	char	*key;
	int		j;

	j = 1;
	while (*(*line + *i + j) != ' ' && *(*line + *i + j) != '='
			&& *(*line + *i + j) != '$' && *(*line + *i + j) != '\0')
	{
		if (*(*line + *i + j) == '\'' && ft_strchr((*line + *i + j + 1), '\'' ))
			break ;
		if (*(*line + *i + j) == '\"')
		{
			if (quote == 1)
				break ;
			else if (ft_strchr((*line + *i + j + 1), '\"'))
				break ;
		}
		j++;
	}
 	temp = ft_substr(*line, 0, *i);
	//printf("---%s---\n",temp);
	key = ft_substr(*line, *i + 1, j - 1);
	//printf("---%s---\n",key);
	lst = search_var(key);
	free(key);
	if (lst)
	{
		temp2 = ft_strjoin(temp, ((t_var *)lst->vol)->value);
	//	printf("---%s---\n",temp2);
		free(temp);
		temp = temp2;
	}
	//char	*ft_multi_strjoin(int len, ...)
	temp2 = ft_strdup(*line + *i + j);
	//printf("---%s---%d\n",*line + *i + j,j);
	//exit(0);
	free(*line);
 	*line = ft_strjoin(temp, temp2);
	//exit(0);
	free(temp);
	free(temp2);
	if(lst)
		*i = *i + ft_strlen(((t_var *)lst->vol)->value) - 1;
	else
		*i = *i -1;
}

void	check_dollar(char **line, int *i, int quote)
{
	if (*(*line + *i + 1) == '\"')
	{
		if (quote == -1 && ft_strchr((*line + *i + 2), '\"'))
			remove_dollar(line, i);
		if (quote == 1)
			return ;
	}
	else if (*(*line + *i + 1) == '\'')
	{
		if (ft_strchr((*line + *i + 2), '\''))
			remove_dollar(line, i);
	}
	else if (*(*line + *i + 1) == '$')
	{
		(*i)++;
		printf("decidir o que fazer\n");
	}
	else if (*(*line + *i + 1) == ' ' || *(*line + *i + 1) == '=')
		return ;
	else
		replace_dollar(line, i, quote);
}


void	correct_line(char **line)
{
	int		db_quote;
	int		sp_quote;
	int		i;

	i = -1;
	db_quote = -1;
	sp_quote = -1;
	correct_redirects(line);
	while (*(*line + ++i))
	{
		if (*(*line + i) == '\'')
			sp_quote *= on_off_quotes((*line + i), sp_quote, db_quote, '\'');
		if (*(*line + i) == '\"')
			db_quote *= on_off_quotes((*line + i), db_quote, sp_quote, '\"');
		if (*(*line + i) == '$' && sp_quote == -1)
			check_dollar(line, &i, db_quote);
	}
}