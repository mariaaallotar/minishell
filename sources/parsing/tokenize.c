/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:23:05 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/24 19:37:58 by eberkowi         ###   ########.fr       */
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

//Left off here! Right now it's just the SAME as strdup
//Need to make it actually not dup the quotes by starting at index 1 and stopping
//before it hits the closing quote
static char	*strdup_with_remove_quotes(const char *s1)
{
	int		i;
	char	*s2;

	s2 = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
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
		if (is_quote((main->split_input[*spl_id])[0]))
			(*command)[cmd_id].command[i] = strdup_with_remove_quotes(main->split_input[*spl_id]);
		else
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
