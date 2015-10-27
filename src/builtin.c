/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 11:19:00 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/27 11:38:27 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	launch_builtin(char **entry)
{
	if (!ft_strcmp(entry[0], "~"))
		built_cd(entry);
	else if (!ft_strcmp(entry[0], "env") ||
		(!ft_strcmp(entry[0], "setenv") && !entry[1]))
		built_env(entry);
	else if (entry[1] && !ft_strcmp(entry[0], "setenv"))
		built_setenv(&entry[1]);
	else if (!ft_strcmp(entry[0], "unsetenv"))
		built_unsetenv(&entry[1]);
	else if (!ft_strcmp(entry[0], "cd"))
		built_cd(entry);
	else if (!ft_strcmp(entry[0], "exit"))
		built_exit(entry);
	else
		return (0);
	return (1);
}
