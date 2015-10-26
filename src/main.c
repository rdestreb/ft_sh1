/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 12:21:15 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/26 15:11:03 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	rec_signal(int sig)
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
		print_error("Segmentation Fault !\n");
	if (sig == SIGTERM)
		ft_putstr_fd("\n", 2);
}

int			main(int ac, char **av, char **env)
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
