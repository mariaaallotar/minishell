/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_without_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:31:32 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/07 13:10:16 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*get_smallest_node(t_list *env_list)
{
	t_list	*smallest;
	t_list	*current;

	smallest = env_list;
	current = env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->content, smallest->content, 50) < 0)
			smallest = current;
		current = current->next;
	}
	return (smallest);
}

t_list	*get_biggest_node(t_list *env_list)
{
	t_list	*biggest;
	t_list	*current;

	biggest = env_list;
	current = env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->content, biggest->content, 50) > 0)
			biggest = current;
		current = current->next;
	}
	return (biggest);
}

t_list	*get_next_node(t_list *prev_node, t_list *biggest_node,
	t_list *env_list)
{
	t_list	*next_node;
	t_list	*current_node;

	current_node = env_list;
	next_node = biggest_node;
	while (current_node != NULL)
	{
		if (ft_strncmp(current_node->content, next_node->content, 50) < 0
			&& ft_strncmp(current_node->content, prev_node->content, 50) > 0)
			next_node = current_node;
		current_node = current_node->next;
	}
	return (next_node);
}

int	export_without_args(t_main *main)
{
	t_list	*prev_node;
	t_list	*cur_node;
	t_list	*biggest_node;

	if (main->env_list == NULL)
		return (0);
	prev_node = get_smallest_node(main->env_list);
	biggest_node = get_biggest_node(main->env_list);
	printf("%s\n", (char *) prev_node->content);
	if (prev_node == biggest_node)
		return (0);
	while (1)
	{
		cur_node = get_next_node(prev_node, biggest_node, main->env_list);
		if (ft_strncmp(cur_node->content, "_=", 2) != 0)
			printf("%s\n", (char *) cur_node->content);
		if (cur_node == biggest_node)
			return (0);
		prev_node = cur_node;
	}
	return (1);
}
