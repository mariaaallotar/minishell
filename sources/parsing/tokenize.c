/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:23:05 by eberkowi          #+#    #+#             */
/*   Updated: 2024/10/23 15:28:52 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_for_pipe_error(t_main *main, t_tokens **tokens)
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
	(*tokens)[cmd_id].command = malloc((main->elements_in_command + 1) * sizeof(char *));
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

int	tokenize(t_main *main, t_tokens **tokens)
{
	int	cmd_id;
	int	spl_id;
	int first_loop;

	if (check_for_pipe_error(main, tokens))
		return (1);
	if (check_for_redirect_error(main, tokens))
		return (1);
	cmd_id = 0;
	spl_id = 0;
	first_loop = 1;
	while (cmd_id < main->num_of_pipes + 1)
	{
		if (first_loop == 1)
		{
			count_elements_in_command(main, spl_id);
			malloc_commands(main, tokens, cmd_id);
			main->id_command = 0;
			first_loop = 0;
		}
		add_in_or_heredoc(main, tokens, cmd_id, &spl_id);
		if (main->split_input[spl_id])
			add_out_or_append(main, tokens, cmd_id, &spl_id);
		add_command(main, tokens, cmd_id, &spl_id);
		if (!main->split_input[spl_id] || main->split_input[spl_id][0] == '|')
		{
			cmd_id++;
			spl_id++;
			first_loop = 1;
		}
	}
	return (0);
}
