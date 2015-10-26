/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 08:56:33 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/26 09:28:31 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*get_path(char **entry)
{
	t_env	*env_line;

	if (!entry[1])
	{
		if ((env_line =	get_env_var("HOME")))
			return (env_line->val);
	}
	else if (!ft_strncmp(entry[1], "~", 1))
	{
		if ((env_line =	get_env_var("HOME")))
			return (ft_strjoin(env_line->val, entry[1] + 1));
	}
	else if (entry[1] && !ft_strcmp(entry[1], "-"))
	{
		if ((env_line = get_env_var("OLDPWD")))
			return (env_line->val);
	}
	return (entry[1]);
}

void		built_cd(char **entry)
{
	char	*path;
	char	*pwd;

	path = get_path(entry);
	pwd = getcwd(NULL, 0);
	if (!access(path, F_OK) && access(path, X_OK))
		return (ft_putendl("\033[33mPermission denied !\033[0m"));
	if (chdir(path) == -1)
		return (ft_putendl("\033[33mNo Such Directory !\033[0m"));
	if (!get_env_var("PWD"))
		add_link("PWD", getcwd(NULL, 0));
	else
		chg_env_var("PWD", getcwd(NULL, 0));
	if (!get_env_var("OLDPWD"))
		add_link("OLDPWD", pwd);
	else
		chg_env_var("OLDPWD", pwd);
}
