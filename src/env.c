/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/15 12:33:29 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/26 15:20:25 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	copy_env(char **env)
{
	char	**split;
	int		i;

	i = -1;
	while (env[++i])
	{
		split = ft_strsplit(env[i], '=');
		add_link(split[0], split[1]);
		ft_strdel(split);
	}
}

char	**disp_env(void)
{
	t_env	*sh_env;
	char	**tab_env;
	int		i;

	if (!(tab_env = (char **)ft_memalloc(sizeof(char *) * (list_size() + 1))))
		return (NULL);
	sh_env = singleton();
	sh_env = sh_env->next;
	i = -1;
	while (sh_env)
	{
		tab_env[++i] = ft_strjoin(ft_strjoin(sh_env->var, "="), sh_env->val);
		sh_env = sh_env->next;
	}
	return (tab_env);
}

t_env	*get_env_var(char *var)
{
	t_env	*get;

	get = singleton();
	get = get->next;
	while (get)
	{
		if (!(ft_strcmp(var, get->var)))
			return (get);
		get = get->next;
	}
	return (NULL);
}

void	chg_env_var(char *var, char *new_val)
{
	t_env	*env_line;

	if (!(env_line = get_env_var(var)))
		return ;
	ft_strdel(&env_line->val);
	if (new_val)
		env_line->val = ft_strdup(new_val);
	else
		env_line->val = ft_strdup("");
}
