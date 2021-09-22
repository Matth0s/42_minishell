/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 01:52:49 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/20 10:15:59 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_struct(t_flag *flag)
{
	(*flag).sin = 0;
	(*flag).zero = 0;
	(*flag).width = -1;
	(*flag).press = -1;
	(*flag).j = 1;
}
