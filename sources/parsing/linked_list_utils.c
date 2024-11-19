/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:02:21 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/18 12:25:11 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			return (NULL);
	}
	else
	{
		new_node->name = ft_strdup(name);
		if (!new_node->name)
			return (NULL);
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
