/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:23:05 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/25 13:55:19 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void check_for_pipe_error(t_main *main, t_command **command)
{
	int i;

	i = 0;
	while (main->split_input[i])
	{
		if ((main->split_input[i])[0] == '|'
			&& !(main->split_input[i + 1]))
		{
				printf("Error: Pipe followed by NULL\n");
				free_and_exit_spl_and_cmd(main, command, 2); //TODO change to not exit, just skip execution	
		}
		i++;
	}
}

void tokenize(t_main *main, t_command **command)
{
	int cmd_id;
	int spl_id;

	check_for_pipe_error(main, command);
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
