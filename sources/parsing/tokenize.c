/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:23:05 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/24 12:17:48 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_elements_in_command(t_main *main, int spl_id)
{
	int result;

	result = 0;
	while (main->split_input[spl_id] && !is_special(main->split_input[spl_id][0]))
	{
		spl_id++;
		result++;
	}
	return (result);
}

static void add_command(t_main *main, t_command **command, int cmd_id, int *spl_id)
{
	int element_count;
	int i;

	//Count elements
	element_count = count_elements_in_command(main, *spl_id);
	if (element_count == 0)
		return ;

	//Malloc command array of strings
	(*command)[cmd_id].command = malloc((element_count + 1) * sizeof(char *));
	if (!(*command)[cmd_id].command)
	{
		printf("Error: Failed to malloc command array in struct\n");
		free_all_and_exit(main, command, 1);
	}

	//Add elements to command
	i = 0;
	while (i < element_count)
	{
		(*command)[cmd_id].command[i] = NULL;
		(*command)[cmd_id].command[i] = ft_strdup(main->split_input[*spl_id]);
		if (!(*command)[cmd_id].command[i])
		{
			printf("Error: Failed to malloc add element to command\n");
			free_all_and_exit(main, command, 1);
		}
		(*spl_id)++;
		i++;
	}
	(*command)[cmd_id].command[i] = NULL;
}

void tokenize(t_main *main, t_command **command)
{
	int cmd_id;
	int spl_id;

	check_for_redirect_error(main, command);
	cmd_id = 0;
	spl_id = 0;
	while (cmd_id < main->num_of_pipes + 1)
	{
		//printf("# 1 cmd_id = %d, spl_id = %d\n", cmd_id, spl_id); //REMOVE
		add_in_or_heredoc(main, command, cmd_id, &spl_id);
		//printf("# 2 cmd_id = %d, spl_id = %d\n", cmd_id, spl_id); //REMOVE
		add_out_or_append(main, command, cmd_id, &spl_id);
		//printf("# 3 cmd_id = %d, spl_id = %d\n", cmd_id, spl_id); //REMOVE
		add_command(main, command, cmd_id, &spl_id);
		//printf("# 4 cmd_id = %d, spl_id = %d\n", cmd_id, spl_id); //REMOVE
		if (!main->split_input[spl_id] || main->split_input[spl_id][0] == '|')
		{
			cmd_id++;
			spl_id++;
		}	
	}
	//TODO function for expanding heredocs with a temp_file that holds the input
}
