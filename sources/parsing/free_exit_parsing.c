/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:44:31 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/24 12:08:59 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_and_exit_spl_and_cmd(t_main *main, t_command **command, int code)
{
	ft_free_split(&main->split_input);
	free(*command);
	exit (code);	
}

void	free_command_token(t_main *main, t_command **command)
{
	int i;
	
	i = 0;
	while (i < main->num_of_pipes + 1)
	{
		if ((*command)[i].command)
			ft_free_split(&(*command)[i].command);
		i++;
	}
}

void free_all_and_exit(t_main *main, t_command **command, int code)
{
	ft_free_split(&main->split_input);
	free_command_token(main, command);
	free(*command);
	exit (code);
}
