/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 08:56:33 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/27 12:26:04 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*get_path(char **entry)
{
	t_env	*env_line;

	if (!entry[1] || !ft_strcmp(entry[1], "--"))
	{
		if ((env_line = get_env_var("HOME")))
			return (env_line->val);
	}
	else if (!ft_strncmp(entry[1], "~", 1))
	{
		if ((env_line = get_env_var("HOME")))
			return (ft_strjoin(env_line->val, entry[1] + 1));
	}
	else if (entry[1] && !ft_strcmp(entry[1], "-"))
	{
		if ((env_line = get_env_var("OLDPWD")))
			return (env_line->val);
	}
	return (entry[1]);
}

static void	verif_cd(char *path)
{
	t_stat	*p_stat;

	if (!(p_stat = (t_stat *)ft_memalloc(sizeof(t_stat))))
		return ;
	if (path)
		stat(path, p_stat);
	if ((!path || !ft_strcmp(path, "~")) && !get_env_var("HOME"))
		return (ft_putendl("\033[33menv. var. HOME missing !\033[0m"));
	else if (path && !ft_strcmp(path, "-") && !get_env_var("OLDPWD"))
		return (ft_putendl("\033[33menv. var. OLDPWD missing !\033[0m"));
	else if (!access(path, F_OK) && !S_ISDIR(p_stat->st_mode))
		return (ft_putendl("\033[33mNot a Directory !\033[0m"));
	else if (!access(path, F_OK) && access(path, X_OK))
		return (ft_putendl("\033[33mPermission denied !\033[0m"));
	else if (chdir(path) == -1)
		return (ft_putendl("\033[33mNo Such Directory !\033[0m"));
}

void		built_cd(char **entry)
{
	char	*path;
	char	*pwd;

	path = get_path(entry);
	pwd = getcwd(NULL, 0);
	verif_cd(path);
	if (!get_env_var("PWD"))
		add_link("PWD", getcwd(NULL, 0));
	else
		chg_env_var("PWD", getcwd(NULL, 0));
	if (!get_env_var("OLDPWD"))
		add_link("OLDPWD", pwd);
	else
		chg_env_var("OLDPWD", pwd);
}
