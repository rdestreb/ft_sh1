/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/27 11:40:41 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/28 09:06:21 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	print_env(void)
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

static void	built_env2(char **entry)
{
	t_env	*tmp;
	char	**new_line;
	char	**tmp_env;

	new_line = ft_strsplit(entry[1], '=');
	if ((tmp = get_env_var(new_line[0])))
	{
		tmp_env = (char **)ft_memalloc(sizeof(tmp));
		tmp_env[0] = ft_strdup(tmp->var);
		tmp_env[1] = ft_strdup(tmp->val);
	}
	built_setenv(new_line);
	if (!entry[2])
		print_env();
	else
		new_process(&entry[2]);
	if (!tmp)
		built_unsetenv(&new_line[0]);
	else
		built_setenv(tmp_env);
}

void		built_env(char **entry)
{
	pid_t	proc;

	if (!entry[1])
		print_env();
	else if (entry[1] && ft_strchr(entry[1], '='))
		built_env2(entry);
	else if (entry[1] && !ft_strcmp(entry[1], "-i"))
	{
		if (entry[2])
		{
			proc = fork();
			if (proc > 0)
				wait(0);
			else
				exec_me(&entry[2], FALSE);
		}
	}
	else
		new_process(&entry[1]);
}
