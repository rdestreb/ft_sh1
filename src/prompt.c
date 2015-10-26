/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 11:17:15 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/26 11:17:22 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	disp_prompt(void)
{
	char	*disp;
	t_env	*home;
	t_env	*pwd;

	home = get_env_var("HOME");
	pwd = get_env_var("PWD");
	if (!pwd)
		disp = ft_strdup(" ");
	else if (!home || !(ft_strstr(pwd->val, home->val)))
		disp = pwd->val;
	else
		disp = ft_strjoin("~",
				ft_strstr(pwd->val, home->val) + ft_strlen(home->val));
	ft_putstr("\033[36;1m[\033[00m\033[1;37m");
	ft_putstr(disp);
	ft_putstr("\033[00m\033[36;1m]> \033[00m");
}
