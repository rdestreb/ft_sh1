/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 12:21:15 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/26 09:21:18 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>
void	print_error(char *msg)
{
	ft_putstr_fd("\033[31mft_sh1 : Error : ", 2);
	ft_putstr_fd(msg, 2);
	exit(2);
}

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
		disp = ft_strjoin("~", ft_strstr(pwd->val, home->val) + ft_strlen(home->val));
	ft_putstr("\033[36;1m[\033[00m\033[1;37m");
	ft_putstr(disp);
	ft_putstr("\033[00m\033[36;1m]> \033[00m");
//	free(disp);
}

pid_t	new_process(void)
{
	pid_t	proc_id;

	if ((proc_id = fork()) == -1)
		print_error("fork failed!");
	return (proc_id);
}

void	exec_me(char **entry)
{
	char	**tab_env;
	char	**tab_path;
	t_env	*path;
	int		i;

	tab_env = disp_env();
	path = get_env_var("PATH");
	tab_path = ft_strsplit(path->val, ':');
	i = -1;
	while (tab_path[++i])
	{
		tab_path[i] = ft_strjoin(ft_strjoin(tab_path[i], "/"), entry[0]);
		execve(tab_path[i], entry, tab_env);
	}
//		free(tab_env);
	print_error(ft_strjoin(entry[0], " command not found\n"));
}

char	*str_clean(char *str)
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

void	get_cmd(char *line)
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

void	enter_shell(void)
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

void	rec_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		disp_prompt();
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\n", 2);
		disp_prompt();
	}
	if (sig == SIGSEGV)
		print_error("Segmentation Fault !");
	if (sig == SIGTERM)
		ft_putstr_fd("\n", 2);
}

int		main(int ac, char **av, char **env)
{

	(void)av;
	if (ac == 1)
	{
		copy_env(env);
		signal(SIGINT, rec_signal);
		signal(SIGQUIT, rec_signal);
		signal(SIGSEGV, rec_signal);
		signal(SIGTERM, rec_signal);
		enter_shell();
	}
	return (0);
}
