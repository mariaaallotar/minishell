/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_and_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:33:07 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/07 13:16:02 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_variable(t_main *main, char *var)
{
	t_list	*node;
	char	*malloced_content;

	node = find_node(main, var);
	free(node->content);
	malloced_content = ft_strdup(var);
	if (malloced_content == NULL)
	{
		//TODO error
		free_environment(&(main->env_list));
		ft_free_split(&(main->split_input));
	}
	node->content = malloced_content;
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

void	export(t_main *main, t_tokens token)
{
	int	i;
	//TODO how to handle export without arguments
	i = 1;
	while (token.command[i] != NULL)	
	{
		if (forbidden_key(token.command[i]))
		{
			//TODO what error to print
			printf("Forbidden key: ");
			while (*(token.command[i]) != '=' && *(token.command[i]))
			{
				printf("%c", *token.command[i]);
				(token.command[i])++;
			}
			printf("\n");
			return ;
		}
		if (existing_key(main, token.command[i]))
			update_variable(main, token.command[i]);
		else
			add_variable(main, token.command[i]);
		i++;
	}
}

void	unset(t_main *main, t_tokens token)
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
			return ;
		}
		joined_str = ft_strjoin(token.command[i], "=");
		if (joined_str == NULL)
		{
			//error;	TODO
			exit(1);
		}
		node = find_node(main, joined_str);
		if (node == NULL)
		{
			free(joined_str);
			return ;
		}
		remove_variable(main, joined_str);
		free(joined_str);
		i++;
	}
}
