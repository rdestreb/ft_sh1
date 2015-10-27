/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 11:04:28 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/27 11:19:27 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		*str_clean(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
	}
	return (str);
}

static void		get_cmd(char *line)
{
	char	**many_cmd;
	char	**entry;
	int		i;

	many_cmd = ft_strsplit(str_clean(line), ';');
	i = -1;
	while (many_cmd[++i])
	{
		entry = ft_strsplit(many_cmd[i], ' ');
		if (entry && *entry && !launch_builtin(entry))
			new_process(entry);
	}
}

void			enter_shell(void)
{
	char	*line;

	while (666)
	{
		disp_prompt();
		if (!(get_next_line(0, &line)))
		{
			ft_putendl("exit");
			exit(0);
		}
		if (*line)
			get_cmd(line);
	}
}
