/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 11:03:02 by rdestreb          #+#    #+#             */
/*   Updated: 2015/10/28 09:30:24 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env	*singleton(void)
{
	static t_env	*lst = NULL;

	if (!lst)
		lst = (t_env *)ft_memalloc(sizeof(t_env));
	return (lst);
}

t_env	*newnode(char *var, char *val)
{
	t_env *new;

	new = ft_memalloc(sizeof(t_env));
	new->var = ft_strdup(var);
	if (!val)
		new->val = ft_strdup("");
	else
		new->val = ft_strdup(val);
	new->next = NULL;
	return (new);
}

t_env	*add_link(char *var, char *val)
{
	t_env	*new;

	new = singleton();
	while (new->next)
		new = new->next;
	new->next = newnode(var, val);
	return (singleton());
}

void	suppr_link(char *var)
{
	t_env	*tmp;
	t_env	*lst;

	lst = singleton();
	while (lst->next && lst->next->next)
	{
		if (!ft_strcmp(lst->next->var, var))
		{
			tmp = lst->next->next;
			free(lst->next);
			lst->next = tmp;
		}
		else
			lst = lst->next;
	}
	if (!ft_strcmp(lst->next->var, var))
	{
		free(lst->next);
		lst->next = NULL;
	}
}

int		list_size(void)
{
	t_env	*lst;
	int		size;

	lst = singleton();
	lst = lst->next;
	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
