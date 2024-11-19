/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_environment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:31:28 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/19 14:12:24 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO this is not tested if we want to implment it

int	get_magnitude(int n)
{
	char	*as_string;

	as_string = ft_itoa(n);
	return (ft_strlen(as_string));
}

void	increment_shell_level(t_list *node)
{
	int		previous_level;
	int		new_level;
	char	*start_of_value;
	char	*new_str;

	start_of_value = ft_strchr(node->content, '=');
	previous_level = ft_atoi(start_of_value + 1);
	new_level = previous_level + 1;
	if (previous_level % 10 == 9)
	{
		new_str = malloc ((ft_strlen(node->content) + 2) * sizeof(char));
		ft_memmove(new_str, node->content, 6 * sizeof(char));
		ft_memmove(new_str + 6, ft_itoa(new_level), get_magnitude(new_level));
		free(node->content);
		node->content = new_str;
	}
	ft_memmove(node->content + 6, ft_itoa(new_level), get_magnitude(new_level));
}

void	update_env(t_main *main)
{
	t_list	*current_node;

	current_node = main->env_list;
	while (current_node != NULL)
	{
		if (ft_strncmp(current_node->content, "SHLVL=", 6) == 0)
		{
			increment_shell_level(&current_node);
		}
	}
}
