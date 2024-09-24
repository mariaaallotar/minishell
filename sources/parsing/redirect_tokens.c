/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:13:07 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/24 12:15:13 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void add_in_or_heredoc(t_main *main, t_command **command, int cmd_id, int *spl_id)
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

void add_out_or_append(t_main *main, t_command **command, int cmd_id, int *spl_id)
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

void check_for_redirect_error(t_main *main, t_command **command)
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
