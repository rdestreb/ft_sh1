/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/27 11:45:59 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/27 11:46:00 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	built_exit(char **entry)
{
	int	val;

	if (!entry[1])
	{
		ft_putendl("exit");
		exit(0);
	}
	else
	{
		val = ft_atoi(entry[1]);
		if (!ft_strcmp(entry[1], ft_itoa(val)))
		{
			ft_putendl("exit");
			exit(val);
		}
		ft_putendl("\033[33mexit : error : wrong syntax\033[0m");
	}
}
