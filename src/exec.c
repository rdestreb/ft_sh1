/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 11:16:54 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/26 12:12:29 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	exec_me(char **entry)
{
	char	**tab_env;
	char	**tab_path;
	t_env	*path;
	int		i;

	tab_env = disp_env();
	if (!access(entry[0], F_OK) && access(entry[0], X_OK))
		print_error(ft_strjoin(entry[0], " Permission denied !\n"));
	else if (!access(entry[0], F_OK) && !access(entry[0], X_OK))
		execve(entry[0], entry, tab_env);
	path = get_env_var("PATH");
	tab_path = ft_strsplit(path->val, ':');
	i = -1;
	while (tab_path[++i])
	{
		tab_path[i] = ft_strjoin(ft_strjoin(tab_path[i], "/"), entry[0]);
		execve(tab_path[i], entry, tab_env);
	}
	print_error(ft_strjoin(entry[0], " command not found\n"));
}
