/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:22:26 by eberkowi          #+#    #+#             */
/*   Updated: 2024/11/21 13:40:12 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_error(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	return (1);
}

void	free_input_and_split(t_main *main)
{
	if (main->input)
		free(main->input);
	if (main->split_input)
		ft_free_split(&main->split_input);
}
