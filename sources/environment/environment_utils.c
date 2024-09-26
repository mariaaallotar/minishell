/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:05 by maheleni          #+#    #+#             */
/*   Updated: 2024/09/26 12:47:10 by maheleni         ###   ########.fr       */
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
		free(current_node->content);
		free(current_node);
		current_node = temp;
	}
}

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

void    add_variable(t_main *main, char *content)
{
    t_list  *new_node;

    new_node = ft_lstnew(ft_strdup(content));
    if (new_node == NULL)
    {
        perror("Error");
        ft_free_split(&(main->split_input));
        free_environment(&(main->env_list));
    }
    ft_lstadd_back(&(main->env_list), new_node);
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

t_list	*copy_env(char *envp[], t_main *main)
{
	t_list	*env_list;
	t_list	*new;
	int		i;

	new = ft_lstnew(ft_strdup(envp[0]));
	if (new == NULL)
	{
		perror("Error");
        ft_free_split(&(main->split_input));
	}
	env_list = new;
	main->env_list = env_list;
	i = 1;
	while (envp[i] != NULL)
	{
		add_variable(main, envp[i]);
		i++;
	}
	return (env_list);
}
