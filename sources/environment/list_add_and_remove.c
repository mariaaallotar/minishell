/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_and_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:29 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/27 15:57:14 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*find_node(t_main *main, char *variable)
{
	t_list	*current_node;
	const char *equal_sign_maybe = ft_strchrnul(variable, '=');
	const size_t len_to_compare = equal_sign_maybe - variable;
	size_t max_len;
	size_t length_to_equal_sign;

	current_node = main->env_list;
	while (current_node != NULL)
	{
		length_to_equal_sign = ft_strchrnul(current_node->content, '=') - (char *)current_node->content;
		if (length_to_equal_sign < len_to_compare)
			max_len = len_to_compare;
		else
			max_len = length_to_equal_sign;
		if (current_node->content
			&& ft_strncmp(variable, current_node->content, max_len) == 0)
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
	if (ft_strchr(var, '=') == NULL && node != NULL)
	{
		return (0);
	}
	if (node == NULL)
	{
		return (1);
	}
	free(node->content);
	malloced_content = ft_strdup(var);
	if (malloced_content == NULL)
	{
		node->content = NULL;
		return (errno);
	}
	node->content = malloced_content;
	return (0);
}

int	add_variable(t_main *main, char *content)
{
	t_list	*new_node;
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

int	set_node_and_prev_node(t_list **previous_node, t_list **node,
	char *variable_key)
{
	char	*temp;

	while (*node != NULL)
	{
		temp = ft_strjoin((*node)->content, "=");
		if (temp == NULL)
		{
			perror("unset");
			return (-1);
		}
		if (ft_strncmp(temp, variable_key, ft_strlen(variable_key)) == 0)
			break ;
		free(temp);
		temp = NULL;
		*previous_node = *node;
		*node = (*previous_node)->next;
	}
	if (temp)
		free(temp);
	return (0);
}

void	remove_variable(t_main *main, char *variable_key)
{
	t_list	*previous_node;
	t_list	*node;
	t_list	*next_node;

	if (main->env_list == NULL)
		return ;
	node = main->env_list;
	previous_node = NULL;
	if (set_node_and_prev_node(&previous_node, &node, variable_key) == -1)
		return ;
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
