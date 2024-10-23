/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_to_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:37:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/23 11:32:38 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_elements_in_command(t_main *main, int spl_id)
{
	int	result;

	result = 0;
	while (main->split_input[spl_id]
		&& !is_special(main->split_input[spl_id][0]))
	{
		result++;
		spl_id++;
	}
	return (result);
}

static void	malloc_cmds(t_main *main, t_tokens **tokens, int cmd_id, int c)
{
	(*tokens)[cmd_id].command = malloc((c + 1) * sizeof(char *));
	if (!(*tokens)[cmd_id].command)
	{
		printf("Error: Failed to malloc command array in struct\n");
		free_all_and_exit(main, tokens);
	}
}

static void	dup_cmd(t_main *main, t_tokens **tokens, int spl_id, char **cmd)
{
	*cmd = NULL;
	*cmd = ft_strdup(main->split_input[spl_id]);
	if (!*cmd)
	{
		printf("Error: Failed to malloc add element to command\n");
		free_all_and_exit(main, tokens);
	}
}

void	add_command(t_main *main, t_tokens **tokens, int cmd_id, int *spl_id)
{
	int	element_count;
	int	i;

	element_count = count_elements_in_command(main, *spl_id);
	if (element_count == 0)
		return ;
	else if (main->found_command == 1)
	{
		printf("Error: Too many commands\n");
		free_all_and_exit(main, tokens);
	}
	main->found_command = 1;
	malloc_cmds(main, tokens, cmd_id, element_count);
	i = 0;
	while (i < element_count)
	{
		dup_cmd(main, tokens, *spl_id, &(*tokens)[cmd_id].command[i]);
		(*spl_id)++;
		i++;
	}
	(*tokens)[cmd_id].command[i] = NULL;
}
