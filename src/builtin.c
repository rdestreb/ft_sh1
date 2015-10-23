/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 11:19:00 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/23 09:10:17 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	built_env(void)
{
	t_env	*lst;

	lst = singleton();
	lst = lst->next;
	while (lst)
	{
		ft_putstr(lst->var);
		ft_putstr("=");
		ft_putendl(lst->val);
		lst = lst->next;
	}
}

void	built_setenv(char **entry)
{
	t_env	*env_line;

	env_line = get_env_var(entry[1]);
	if (entry[1] && entry[2] && !(env_line))
		add_link(entry[1], entry[2]);
	else if (entry[1] && !entry[2] && !(env_line))
		add_link(entry[1], "");
	else if (env_line)
	{
		if (ft_strcmp(env_line->val, ""))
			free(env_line->val);
		if (entry[2])
			env_line->val = ft_strdup(entry[2]);
		else
			env_line->val = ft_strdup("");
	}
}

void	built_unsetenv(char **entry)
{
	t_env	*env_line;

	if (!entry[1])
		ft_putendl("\033[33munsetenv: too few arguments.\033[0m");
	else
	{
		env_line = get_env_var(entry[1]);
		if (env_line && env_line->var)
			suppr_link(env_line->var);
	}
}


int		launch_builtin(char **entry)
{

	if (!ft_strcmp(entry[0], "env") ||
		(!ft_strcmp(entry[0], "setenv") && !entry[1]))
		built_env();
	else if (entry[1] && !ft_strcmp(entry[0], "setenv"))
		built_setenv(entry);
	else if (!ft_strcmp(entry[0], "unsetenv"))
		built_unsetenv(entry);
	else if (!ft_strcmp(entry[0], "cd"))
		built_cd(entry);
	else if (!ft_strcmp(entry[0], "exit"))
	{
		ft_putendl("exit");
		exit(0);
	}
	else
		return (0);
	return (1);
}
