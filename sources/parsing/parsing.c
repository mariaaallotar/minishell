/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:32:36 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/18 18:41:27 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing(t_main *main)
{
	//main functions
	if (!split_input(main))
		return (0);

	//print for testing
	int i = 0;
	while (main->split_input[i])
	{
		printf("input[%d] = %s\n", i, main->split_input[i]);
		i++;
	}

	//builtins
	exit_command(main);
	
	//free and null
	if (*main->input)
	{
		free(main->input);
		main->input = NULL;
	}
	if (main->split_input)
	{
		ft_free_split(&main->split_input);
		main->split_input = NULL;
	}
	return (1);
}
