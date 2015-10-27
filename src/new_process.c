/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <rdestreb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/27 11:53:21 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/27 11:53:22 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	new_process(char **entry)
{
	pid_t	proc_id;

	if ((proc_id = fork()) == -1)
		print_error("fork failed!");
	if (proc_id > 0)
		wait(0);
	else
		exec_me(entry);
}
