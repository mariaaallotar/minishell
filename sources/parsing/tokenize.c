/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:23:05 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/04 11:19:02 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_pipe_error(t_main *main, t_tokens **tokens)
{
	int	i;

	i = 0;
	while (main->split_input[i])
	{
		if ((main->split_input[i])[0] == '|'
			&& !(main->split_input[i + 1]))
		{
			printf("Error: Pipe followed by NULL\n");
			free_split_and_tokens(main, tokens);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	malloc_commands(t_main *main, t_tokens **tokens, int cmd_id)
{
	int	temp;

	temp = main->elements_in_command;
	(*tokens)[cmd_id].command = malloc((temp + 1) * sizeof(char *));
	if (!(*tokens)[cmd_id].command)
	{
		printf("Error: Failed to malloc command array in struct\n");
		free_all_and_exit(main, tokens);
	}
}

static void	count_elements_in_command(t_main *main, int spl_id)
{
	main->elements_in_command = 0;
	while (main->split_input[spl_id] && main->split_input[spl_id][0] != '|')
	{
		(main->elements_in_command)++;
		spl_id++;
	}
}

static void init_tokenize_vars(int *cmd_id, int *spl_id, bool *first_loop)
{
	*cmd_id = 0;
	*spl_id = 0;
	*first_loop = true;	
}

void	tokenize(t_main *main, t_tokens **tokens)
{
	int		cmd_id;
	int		spl_id;
	bool	first_loop;

	init_tokenize_vars(&cmd_id, &spl_id, &first_loop);
	while (cmd_id < main->num_of_pipes + 1)
	{
		if (first_loop)
		{
			count_elements_in_command(main, spl_id);
			malloc_commands(main, tokens, cmd_id);
			main->id_command = 0;
			first_loop = false;
		}
		add_in_or_heredoc(main, tokens, cmd_id, &spl_id);
		if (main->split_input[spl_id])
			add_out_or_append(main, tokens, cmd_id, &spl_id);
		add_command(main, tokens, cmd_id, &spl_id);
		if (!main->split_input[spl_id] || main->split_input[spl_id][0] == '|')
		{
			cmd_id++;
			spl_id++;
			first_loop = true;
		}
	}
}
