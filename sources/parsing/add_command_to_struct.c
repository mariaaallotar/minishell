/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_to_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:37:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/18 13:36:07 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	dup_cmd(t_main *main, t_tokens **tokens, int spl_id, char **cmd)
{
	*cmd = NULL;
	*cmd = ft_strdup(main->split_input[spl_id]);
	if (!*cmd)
	{
		print_error("Error: Failed to malloc add element to command\n");
		free_all_and_exit(main, tokens);
	}
}

void	add_command(t_main *main, t_tokens **tokens, int cmd_id, int *spl_id)
{
	while (main->split_input[*spl_id]
		&& !char_is_special(main->split_input[*spl_id][0]))
	{
		dup_cmd(main, tokens, *spl_id,
			&(*tokens)[cmd_id].command[main->id_command]);
		(*spl_id)++;
		(main->id_command)++;
	}
	(*tokens)[cmd_id].command[main->id_command] = NULL;
}
