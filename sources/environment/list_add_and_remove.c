/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_and_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:29 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/17 14:09:05 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*find_node(t_main *main, char *variable)
{
	int		key_len;
	t_list	*current_node;

	key_len = ft_strchr(variable, '=') - variable;
	current_node = main->env_list;
	while (current_node != NULL)
	{
		if (ft_strncmp(variable, current_node->content, key_len) == 0)
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
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
    ft_lstadd_back(&(main->env_list), new_node);
	return (0);
}

void	remove_variable(t_main *main, char *variable_key)
{
	t_list	*previous_node;
	t_list	*current_node;
	t_list	*next_node;
	int		key_len;

	key_len = ft_strlen(variable_key);
	current_node = main->env_list;
	previous_node = NULL;
    while (ft_strncmp(current_node->content, variable_key, key_len))
	{
		previous_node = current_node;
		current_node = previous_node->next;
	}
	next_node = current_node->next;
	free(current_node->content);
	free(current_node);
	if (previous_node == NULL)
		main->env_list = next_node;
	else
		previous_node->next = next_node;
}