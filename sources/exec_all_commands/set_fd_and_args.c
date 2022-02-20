/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_and_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:35:30 by mmoreira          #+#    #+#             */
/*   Updated: 2022/02/20 14:07:57 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_fd(char *name, int flags, int direct, int *fd)
{
	if (*fd != 0 && *fd != 1)
		close(*fd);
	*fd = open(name, flags, 0664);
	if (*fd < 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		*fd = dup(direct);
		return (1);
	}
	return (0);
}

static int	create_fds(char **split, int *fdin, int *fdout)
{
	if (!(strcmp(*split, ">")))
		return (open_fd(*(split + 1), O_WRONLY | O_CREAT | O_TRUNC, 1, fdout));
	else if (!(strcmp(*split, "<")))
		return (open_fd(*(split + 1), O_RDONLY, 0, fdin));
	else if (!(strcmp(*split, ">>")))
		return (open_fd(*(split + 1), O_WRONLY | O_CREAT | O_APPEND, 1, fdout));
	else
		return (set_heredoc(*(split + 1), fdin));
}

static int	create_args(char ***temp, char **split)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (*(split + ++i))
		if (is_operator(*(split + i)))
			j++;
	i = ft_splitlen(split) - j * 2;
	*temp = malloc((i + 1) * sizeof(char *));
	if (!(*temp))
		return (1);
	*(*temp + i) = NULL;
	return (0);
}

char	**set_fds_and_args(char **split, int *fdin, int *fdout)
{
	char	**temp;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (create_args(&temp, split))
		return (NULL);
	while (*(split + ++i))
	{
		if (is_operator(*(split + i)))
		{
			if (*fdin == -1 || create_fds(split + i, fdin, fdout))
				break ;
			i++;
		}
		else
			*(temp + ++j) = ft_strdup(*(split + i));
	}
	if (*fdin == -1 || i != ft_splitlen(split))
	{
		ft_free_split(temp);
		return (NULL);
	}
	return (temp);
}
