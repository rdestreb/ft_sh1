/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 11:16:54 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/26 15:52:35 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	replace_home(char **entry)
{
	t_env	*env_line;
	int		i;

	i = 0;
	while (entry[++i])
	{
		if (entry[i][0] == '~' && (env_line = get_env_var("HOME")))
			entry[i] = ft_strjoin(env_line->val, entry[i] + 1);
	}
}

void	exec_me(char **entry)
{
	char	**tab_env;
	char	**tab_path;
	t_env	*path;
	int		i;

	tab_env = disp_env();
	replace_home(entry);
	if (!access(entry[0], F_OK) && access(entry[0], X_OK))
		print_error(ft_strjoin(entry[0], " Permission denied !\n"));
	else if (!access(entry[0], F_OK) && !access(entry[0], X_OK))
		execve(entry[0], entry, tab_env);
	path = get_env_var("PATH");
	if (!path)
		print_error("env. var. PATH missing !\n");
	tab_path = ft_strsplit(path->val, ':');
	i = -1;
	while (tab_path[++i])
	{
		tab_path[i] = ft_strjoin(ft_strjoin(tab_path[i], "/"), entry[0]);
		execve(tab_path[i], entry, tab_env);
	}
	print_error(ft_strjoin(entry[0], " command not found\n"));
}
