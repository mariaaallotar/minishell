/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:05 by maheleni          #+#    #+#             */
/*   Updated: 2024/09/19 15:05:08 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    free_environment(t_list **env_list)
{
	t_list	*current_node;
	t_list	*temp;

	current_node = *env_list;
    while (current_node != NULL)
	{
		temp = current_node->next;
		free(current_node);
		current_node = temp;
	}
}

void    add_variable(t_main *main, char *content)
{
    t_list  *new_node;

    new_node = ft_lstnew(content);
    if (new_node == NULL)
    {
        perror("Error");
        ft_free_split(&(main->split_input));
        free_environment(&(main->env_list));
    }
    ft_lstadd_back(&(main->env_list), new_node);
}

t_list	*copy_env(char *envp[], t_main *main)
{
	t_list	*env_list;
	t_list	*new;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		new = ft_lstnew(envp[i]);
		if (i == 0)
		{
			env_list = new;
			i++;
			continue;
		}
		ft_lstadd_back(&env_list, new);
		i++;
	}
	main->env_list = env_list;
	return (env_list);
}
