/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_strjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:30:06 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/20 13:56:03 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_multi_strjoin(int len, ...)
{
	va_list	args;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	va_start(args, len);
	temp3 = ft_strdup(va_arg(args, char *));
	while (--len)
	{
		temp2 = va_arg(args, char *);
		temp1 = ft_strjoin(temp3, temp2);
		free(temp3);
		temp3 = temp1;
	}
	va_end(args);
	return (temp3);
}
