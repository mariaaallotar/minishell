/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:02:21 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/19 10:09:01 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*free_and_return_null(t_redirect_node **new_node)
{
	free(*new_node);
	return (NULL);
}

t_redirect_node	*lstnew_redirect_node(char *name, int type)
{
	t_redirect_node	*new_node;

	new_node = NULL;
	new_node = (t_redirect_node *)malloc(sizeof(t_redirect_node));
	if (!new_node)
		return (NULL);
	new_node->name = NULL;
	new_node->delimiter = NULL;
	new_node->delimiter_has_quotes = false;
	new_node->next = NULL;
	new_node->type = type;
	if (type == HEREDOC)
	{
		new_node->delimiter = ft_strdup(name);
		if (!new_node->delimiter)
			return (free_and_return_null(&new_node));
	}
	else
	{
		new_node->name = ft_strdup(name);
		if (!new_node->name)
			return (free_and_return_null(&new_node));
	}
	return (new_node);
}

t_redirect_node	*lstlast_redirect_node(t_redirect_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_redirect_node(t_redirect_node **lst, t_redirect_node *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		lstlast_redirect_node(*lst)->next = new;
	else
		*lst = new;
}
