/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:45:01 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/23 03:03:02 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_dollar(char **line, int *i, int ind)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(*line, 0, *i);
	if (ind)
	{
		temp2 = ft_strjoin(temp, "965");
		free(temp);
		temp = temp2;
	}
	temp2 = ft_strdup(*line + *i + 1);
	free(*line);
	*line = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	if (ind)
		*i = --(*i) + 3;
	else
		(*i)--;
}

static int	aux_replace_var_value(char *line, int quote)
{
	int		j;

	j = 1;
	while (*(line + j) != ' ' && *(line + j) != '='
		&& *(line + j) != '$' && *(line + j) != '\0')
	{
		if (*(line + j) == '\'' && ft_strchr((line + j + 1), '\'' ))
			break ;
		if (*(line + j) == '\"')
		{
			if (quote == 1)
				break ;
			else if (ft_strchr((line + j + 1), '\"'))
				break ;
		}
		j++;
	}
	return (j);
}

static void	replace_var_value(char **line, int *i, int quote)
{
	t_list	*lst;
	char	*temp;
	char	*temp2;
	int		j;

	j = aux_replace_var_value(*line + *i, quote);
	temp = ft_substr(*line, 0, *i);
	temp2 = ft_substr(*line, *i + 1, j - 1);
	lst = search_var(temp2);
	free(temp2);
	if (lst)
	{
		temp2 = ft_strjoin(temp, ((t_var *)lst->vol)->value);
		free(temp);
		temp = temp2;
	}
	temp2 = ft_strdup(*line + *i + j);
	free(*line);
	*line = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	if (lst)
		*i = *i - 1 + ft_strlen(((t_var *)lst->vol)->value);
	else
		*i = *i - 1;
}

static void	check_dollar(char **line, int *i, int quote)
{
	if (*(*line + *i + 1) == '\"')
	{
		if (quote == -1 && ft_strchr((*line + *i + 2), '\"'))
			remove_dollar(line, i, 0);
		if (quote == 1)
			return ;
	}
	else if (*(*line + *i + 1) == '\'')
	{
		if (ft_strchr((*line + *i + 2), '\''))
			remove_dollar(line, i, 0);
	}
	else if (*(*line + *i + 1) == '$')
	{
		(*i)++;
		remove_dollar(line, i, 1);
	}
	else if (*(*line + *i + 1) == ' ' || *(*line + *i + 1) == '=')
		return ;
	else
		replace_var_value(line, i, quote);
}

void	replace_dollar(char **line)
{
	int		db_quote;
	int		sp_quote;
	int		i;

	i = -1;
	db_quote = -1;
	sp_quote = -1;
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
