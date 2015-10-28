/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 12:21:27 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/28 09:06:48 by rdestreb         ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0

typedef struct stat		t_stat;
typedef struct s_env	t_env;

struct	s_env
{
	char	*var;
	char	*val;
	t_env	*next;
};

void	print_error(char *msg);
void	copy_env(char **env);
void	enter_shell(void);
void	disp_prompt(void);
void	exec_me(char **entry, int bool);
char	**disp_env(void);
t_env	*singleton(void);
t_env	*newnode(char *var, char *val);
t_env	*add_link(char *var, char *val);
t_env	*get_env_var(char *var);
void	chg_env_var(char *var, char *new_val);
void	suppr_link(char *var);
int		list_size(void);
int		launch_builtin(char **entry);
void	built_cd(char **entry);
void	built_env(char **entry);
void	built_setenv(char **entry);
void	built_unsetenv(char **entry);
void	built_exit(char **entry);
void	new_process(char **entry);

#endif
