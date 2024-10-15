/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:38:24 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/15 16:20:49 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd(t_main *main, t_tokens token)
{
	int	return_value;

	(void) main;
	if (token.command[2] != NULL)
	{
		dup2(STDERR_FILENO, 1);
		printf("Cd only takes one argument\n");
		return (1);
	}
	return_value = chdir(token.command[1]);
	if (return_value == -1)
	{
		perror(NULL);
		return (errno);
	}
	return (0);
}
