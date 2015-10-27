/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/27 11:45:51 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/27 11:45:52 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	built_unsetenv(char **entry)
{
	t_env	*env_line;

	if (!entry[0])
		ft_putendl("\033[33munsetenv: too few arguments.\033[0m");
	else
	{
		env_line = get_env_var(entry[0]);
		if (env_line && env_line->var)
			suppr_link(env_line->var);
	}
}
