/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 12:21:15 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/15 18:33:49 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>
void	print_error(char *msg)
{
	ft_putstr_fd("ft_sh1 : Error : ", 2);
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
	if (!home || !pwd)
		disp = ft_strdup(" ");
	else if (!(ft_strnequ(pwd->val, home->val, ft_strlen(home->val))))
		disp = pwd->val;
	else
		disp = ft_strjoin("~", &pwd->val[ft_strlen(home->val)]);
	ft_putstr("\033[36;1m[\033[00m\033[1;37m");
	ft_putstr(disp);
	ft_putstr("\033[00m\033[36;1m]> \033[00m");
	free(disp);
}

pid_t	new_process(void)
{
	pid_t	proc_id;

	if ((proc_id = fork()) == -1)
		print_error("fork failed!");
	return (proc_id);
}

void	exec_me(char *cmd)
{
//	t_env	*sh_env;
	char	**entry;
	char	**tab_env;
	char	**tab_path;
	t_env	*path;
	int		i;
//	sh_env = singleton();
	entry = ft_strsplit(cmd, ' ');
//	printf("%s\n", cmd);
	tab_env = disp_env();
	path = get_env_var("PATH");
	tab_path = ft_strsplit(path->val, ':');
//	if (ft_strstr(entry[0], "ls"))
	i = -1;
	while (tab_path[++i])
		execve(ft_strjoin(ft_strjoin(tab_path[i],"/"), entry[0]), entry, tab_env);
	print_error(ft_strjoin(cmd, " command not found\n"));
	free(tab_env);
}

int		main(int ac, char **av, char **env)
{
	pid_t	proc1;
//	pid_t	proc2;
	char	*line;

	(void)av;
	if (ac == 1)
	{
		copy_env(env);
//		disp_env();
//		signal(SIGQUIT, SIG_DFL);
		while (666)
		{
			disp_prompt();
			if (!(get_next_line(0, &line)))
			{
				ft_putendl("exit");
				exit(0);
			}
			proc1 = new_process();
			if (proc1 > 0)
				wait(0);
			else
				exec_me(line);
/*			if (ft_strstr(line, "ls"))
			{
				proc1 = new_process();
				if (proc1 > 0)
					wait(0);
				else
					execve("/bin/ls", &line, env);
			}
			else
				ft_putendl(line);
		}
^^	if (ac > 0)
	{
		proc1 = new_process();
		if (proc1 > 0)
		{
			wait(0);
			printf("ID1 : %d\n", proc1);
			execve("/bin/ls", av, env);
		}
		if (proc1 == 0)
		{
			proc2 = new_process();
			if (proc2 > 0)
			{
				wait(0);
				printf("ID1 : %d\n", proc1);
				printf("ID2 : %d\n", proc2);
				execve("/bin/pwd", av, env);
			}
			if (proc2 == 0)
			{
				printf("ID1 : %d\n", proc1);
				printf("ID2 : %d\n", proc2);
				ft_putendl("Hello");
			}
		}
	}
*/
		}
	}
	return (0);
}