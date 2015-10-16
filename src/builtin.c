/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 11:19:00 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/16 13:05:58 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>
void	built_env(char **tab_env)
{
	int	i;

	i = -1;
	while (tab_env[++i])
		ft_putendl(tab_env[i]);
}

void	built_setenv(char **entry)
{
	t_env	*env_line;

	env_line = get_env_var(entry[1]);
	if (entry[1] && entry[2] && !(env_line))
		add_link(entry[1], entry[2]);
	else if (entry[1] && !entry[2] && !(env_line))
		add_link(entry[1], "");
	else if (entry[1] && env_line)
	{
		if (env_line->val)
			free(env_line->val);
		if (entry[2])
			env_line->val = ft_strdup(entry[2]);
		else
			env_line->val = ft_strdup("");
	}
	if (env_line)
		free(env_line);
}

int		launch_builtin(char **entry, char **tab_env)
{

	if (!ft_strcmp(entry[0], "env") ||
		(!ft_strcmp(entry[0], "setenv") && !entry[1]))
		built_env(tab_env);
	else if (!ft_strcmp(entry[0], "setenv"))
		built_setenv(entry);
	else if (!ft_strcmp(entry[0], "unsetenv"))
		;
	else if (!ft_strcmp(entry[0], "cd"))
		;
	else if (!ft_strcmp(entry[0], "exit"))
		;
	else
		return (0);
	return (1);
}
