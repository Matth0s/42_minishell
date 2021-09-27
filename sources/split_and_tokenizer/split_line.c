/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 19:11:03 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/26 19:46:41 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_quotes(char **arg, int *i)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*temp4;
	char	*end;

	end = ft_strchr(*arg + *i + 1, *(*arg + *i));
	temp = ft_substr(*arg, 0, *i);
	temp2 = ft_substr(*arg + *i + 1, 0, end - (*arg + *i + 1 ));
	temp3 = ft_strdup(end + 1);
	temp4 = ft_strjoin(temp, temp2);
	free(*arg);
	*arg = ft_strjoin(temp4, temp3);
	*i = *i - 1 + ft_strlen(temp2);
	free(temp);
	free(temp2);
	free(temp3);
	free(temp4);
	return (-1);
}

static void	split_remove_quotes(char **arg)
{
	int		db_quote;
	int		sp_quote;
	int		i;

	i = -1;
	db_quote = -1;
	sp_quote = -1;
	while (*(*arg + ++i))
	{
		if (*(*arg + i) == '\'')
			sp_quote *= on_off_quotes((*arg + i), sp_quote, db_quote, '\'');
		if (*(*arg + i) == '\"')
			db_quote *= on_off_quotes((*arg + i), db_quote, sp_quote, '\"');
		if (sp_quote == 1)
			sp_quote *= remove_quotes(arg, &i);
		if (db_quote == 1)
			db_quote *= remove_quotes(arg, &i);
	}
}

static void	split_get_args(char ***temp, char *line)
{
	int		db_quote;
	int		sp_quote;
	int		i;
	int		j;

	j = 0;
	i = -1;
	db_quote = -1;
	sp_quote = -1;
	while (*(line + ++i))
	{
		if (*(line + i) == '\'')
			sp_quote *= on_off_quotes((line + i), sp_quote, db_quote, '\'');
		if (*(line + i) == '\"')
			db_quote *= on_off_quotes((line + i), db_quote, sp_quote, '\"');
		if (*(line + i) != ' '
			|| (*(line + i) == ' ' && ((db_quote == 1 || sp_quote == 1))))
			j++;
		if (j && ((*(line + i + 1) == '\0') || (*(line + i + 1) == ' '
					&& (db_quote == -1 && sp_quote == -1))))
		{
			*((*temp)++) = ft_substr(line + i - j + 1, 0, j);
			j = 0;
		}
	}
}

static int	split_number_args(char *line)
{
	int		db_quote;
	int		sp_quote;
	int		args;
	int		i;

	i = -1;
	args = 0;
	db_quote = -1;
	sp_quote = -1;
	while (*(line + ++i))
	{
		if (*(line + i) == '\'')
			sp_quote *= on_off_quotes((line + i), sp_quote, db_quote, '\'');
		if (*(line + i) == '\"')
			db_quote *= on_off_quotes((line + i), db_quote, sp_quote, '\"');
		if (db_quote == -1 && sp_quote == -1)
			if (*(line + i) != ' '
				&& (*(line + i + 1) == ' ' || *(line + i + 1) == '\0'))
				args += 1;
	}
	return (args);
}

int	split_line(char ***split, char *line)
{
	char	**temp;
	char	**temp2;
	int		i;

	i = split_number_args(line);
	if (!(i))
		return (1);
	temp = malloc((i + 1) * sizeof(char *));
	if (!(temp))
		return (1);
	*(temp + i) = NULL;
	temp2 = temp;
	split_get_args(&temp2, line);
	i = -1;
	while (*(temp + ++i))
		split_remove_quotes((temp + i));
	*split = temp;
	return (0);
}
