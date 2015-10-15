/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 12:21:27 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/15 17:44:29 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct s_env	t_env;

struct	s_env
{
	char	*var;
	char	*val;
	t_env	*next;
};

void	copy_env(char **env);
char	**disp_env(void);
t_env	*singleton(void);
t_env	*newnode(char *var, char *val);
t_env	*add_link(char *var, char *val);
t_env	*get_env_var(char *var);
int		list_size(void);

#endif
