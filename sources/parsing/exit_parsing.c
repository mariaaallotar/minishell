/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:22:10 by eberkowi          #+#    #+#             */
/*   Updated: 2024/09/18 14:28:57 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_free_split_element_malloc_failed(t_main *main, int i)
{
	while (i >= 0)
	{
		free(main->split_input[i]);
		i--;
	}
	free(main->split_input);
	free(main->input);
}
