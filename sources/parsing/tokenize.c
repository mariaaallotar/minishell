/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:23:05 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/24 11:27:28 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void add_in_or_heredoc(t_main *main, t_command **command, int cmd_id, int *spl_id)
{
	if (!ft_strncmp(main->split_input[*spl_id], "<", 2))
	{
		(*command)[cmd_id].redirect_in = &main->split_input[*spl_id + 1];
		(*spl_id) += 2;
	}
	else if (!ft_strncmp(main->split_input[*spl_id], "<<", 3))
	{
		(*command)[cmd_id].heredoc_delimiter = &main->split_input[*spl_id + 1];
		(*command)[cmd_id].redirect_heredoc = true;
		(*spl_id) += 2;
	}
}

static void add_out_or_append(t_main *main, t_command **command, int cmd_id, int *spl_id)
{
	if (!main->split_input[*spl_id])
		return ;
	if (!ft_strncmp(main->split_input[*spl_id], ">", 2))
	{
		(*command)[cmd_id].redirect_out = &main->split_input[*spl_id + 1];
		(*spl_id) += 2;
	}
	else if (!ft_strncmp(main->split_input[*spl_id], ">>", 3))
	{
		(*command)[cmd_id].redirect_append = &main->split_input[*spl_id + 1];
		(*spl_id) += 2;
	}
}

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
		ft_free_split(&main->split_input);
		free(*command);
		printf("Error: Failed to malloc command array in struct\n");
	}

	//Add elements to command
	i = 0;
	while (i < element_count)
	{
		(*command)[cmd_id].command[i] = ft_strdup(main->split_input[*spl_id]);
		if (!(*command)[cmd_id].command[i])
		{
			ft_free_split(&main->split_input);
			free(*command);
			printf("Error: Failed to malloc add element to command\n");
		}
		(*spl_id)++;
		i++;
	}
	(*command)[cmd_id].command[i] = NULL;
}

static void check_for_redirect_error(t_main *main, t_command **command)
{
	int i;

	i = 0;
	while (main->split_input[i])
	{
		if (is_redirect((main->split_input[i])[0]))
		{
			if (!(main->split_input[i + 1]))
			{
				printf("syntax error near unexpected token '\\n'\n");
				free_and_exit_spl_and_cmd(main, command, 2);	
			}
			if (is_redirect((main->split_input[i + 1])[0]))
			{
				printf("syntax error near unexpected token '%s'\n", main->split_input[i + 1]);
				free_and_exit_spl_and_cmd(main, command, 2);
			}
		}
		i++;
	}
}

//left off here fixing <infile < infile2, was about to print cmd_id and spl_id  to debug
void tokenize(t_main *main, t_command **command)
{
	int cmd_id;
	int spl_id;

	cmd_id = 0;
	spl_id = 0;
	check_for_redirect_error(main, command);
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
