/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_and_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:29 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/07 16:28:11 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*find_node(t_main *main, char *variable)
{
	int		key_len;
	t_list	*current_node;

	key_len = ft_strchr(variable, '=') - variable;
	if (key_len < 0)
		key_len = ft_strlen(variable);
	current_node = main->env_list;
	while (current_node != NULL)
	{
		if (ft_strncmp(variable, current_node->content, key_len) == 0)
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

int	update_variable(t_main *main, char *var)
{
	t_list	*node;
	char	*malloced_content;

	node = find_node(main, var);
	if (node == NULL)
		return (1);
	free(node->content);
	malloced_content = ft_strdup(var);
	if (malloced_content == NULL)
		return(errno);
	node->content = malloced_content;
	return (0);
}

int    add_variable(t_main *main, char *content)
{
    t_list  *new_node;
	char	*new_content;

	new_content = ft_strdup(content);
	if (new_content == NULL)
		return (errno);
    new_node = ft_lstnew(new_content);
    if (new_node == NULL)
    {
        perror(NULL);
        return (errno);
    }
	if (main->env_list == NULL)
		main->env_list = new_node;
	else
		ft_lstadd_back(&(main->env_list), new_node);
	return (0);
}

void	set_node_and_prev_node(t_list **previous_node, t_list **node,
	char *variable_key)
{
	while (*node != NULL
		&& ft_strncmp((*node)->content, variable_key, ft_strlen(variable_key)))
	{
		*previous_node = *node;
		*node = (*previous_node)->next;
	}
}

void	remove_variable(t_main *main, char *variable_key)
{
	t_list	*previous_node;
	t_list	*node;
	t_list	*next_node;

	variable_key = ft_strjoin(variable_key, "=");
	if (variable_key == NULL)
	{
		perror(NULL);
		return ;
	}
	node = main->env_list;
	previous_node = NULL;
	set_node_and_prev_node(&previous_node, &node, variable_key);
	free(variable_key);
	if (node == NULL)
		return ;
	next_node = node->next;
	free(node->content);
	free(node);
	if (previous_node == NULL)
		main->env_list = next_node;
	else
		previous_node->next = next_node;
	return ;
}