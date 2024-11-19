/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:22:26 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/19 14:27:18 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
}

void	free_input_and_split(t_main *main)
{
	if (main->input)
		free(main->input);
	if (main->split_input)
		ft_free_split(&main->split_input);
}
