/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_and_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:33:07 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/27 12:16:56 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	existing_key(t_main *main, char *var)
{
	if (find_node(main, var) != NULL)
		return (1);
	return (0);
}

int	forbidden_key(char *var)
{
	int	i;

	if (ft_isdigit(var[0]) || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (1);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) || var[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

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

t_list	*get_next_node(t_list *prev_node, t_list *biggest_node, t_list *env_list)
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

	prev_node = get_smallest_node(main->env_list);
	biggest_node = get_biggest_node(main->env_list);
	printf("%s\n", (char *) prev_node->content);
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

void	print_key(char *command)
{
	while (*(command) != '=' && *command)
	{
		printf("%c", *command);
		command++;
	}
}

int	export(t_main *main, t_tokens token)
{
	int	i;

	if (token.command[1] == NULL)
		return (export_without_args(main));
	i = 1;
	while (token.command[i] != NULL)	
	{
		if (ft_strrchr(token.command[i], '=') == NULL)
		{
			i++;
			continue ;
		}
		if (forbidden_key(token.command[i]))
		{
			printf("Forbidden key: ");
			print_key(token.command[i]);
			printf("\n");
			errno = 1;
		}
		else if (existing_key(main, token.command[i]))
		{
			if (update_variable(main, token.command[i]) != 0)
				return (errno);
		}
		else
		{
			if (add_variable(main, token.command[i]) != 0)
				return (errno);
		}
		i++;
	}
	return (errno);
}

int	unset(t_main *main, t_tokens token)
{
	t_list	*node;
	char	*joined_str;
	int		i;

	i = 1;
	while (token.command[i] != NULL)
	{
		if (ft_strchr(token.command[i], '=') != NULL)
		{
			printf("invalid parameter name\n");
			errno = 1;
			i++;
			continue ;
		}
		joined_str = ft_strjoin(token.command[i], "=");
		if (joined_str == NULL)
		{
			perror(NULL);
			i++;
			continue ;
		}
		node = find_node(main, joined_str);
		if (node == NULL)
		{
			free(joined_str);
			i++;
			continue ;
		}
		remove_variable(main, joined_str);
		free(joined_str);
		i++;
	}
	return (errno);
}
