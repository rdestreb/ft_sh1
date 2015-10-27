/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/27 11:45:35 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/27 11:45:37 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	built_setenv(char **entry)
{
	t_env	*env_line;

	env_line = get_env_var(entry[0]);
	if (entry[0] && entry[1] && !(env_line))
		add_link(entry[0], entry[1]);
	else if (entry[0] && !entry[1] && !(env_line))
		add_link(entry[0], "");
	else if (env_line)
	{
		if (ft_strcmp(env_line->val, ""))
			free(env_line->val);
		if (entry[1])
			env_line->val = ft_strdup(entry[1]);
		else
			env_line->val = ft_strdup("");
	}
}
