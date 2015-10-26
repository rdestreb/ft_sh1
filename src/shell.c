/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 11:04:28 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/26 11:04:30 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static pid_t	new_process(void)
{
	pid_t	proc_id;

	if ((proc_id = fork()) == -1)
		print_error("fork failed!");
	return (proc_id);
}

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
	pid_t	proc1;
	int		i;

	many_cmd = ft_strsplit(str_clean(line), ';');
	i = -1;
	while (many_cmd[++i])
	{
		entry = ft_strsplit(many_cmd[i], ' ');
		if (entry && *entry && !launch_builtin(entry))
		{
			proc1 = new_process();
			if (proc1 > 0)
				wait(0);
			else
				exec_me(entry);
		}
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
