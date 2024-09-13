/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:44:33 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/13 14:57:37 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_exit_command(t_main *main)
{
	int exit_code;
	if (!ft_strncmp(main->input, "exit", 5)) //only a test, check notes.txt for cases
	{
		printf("exit\n");
		free(main->input);
		main->exit_code = 0; //Only a test
		exit(main->exit_code);
	}
}
