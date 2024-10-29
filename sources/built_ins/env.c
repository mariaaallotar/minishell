/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:49:12 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/29 14:54:05 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_main *main, t_tokens token)
{
	char	*message;

	if (token.command[1] != NULL)
	{
		message = "env: env does not take any arguments\n";
		write(STDERR_FILENO, message, ft_strlen(message));
		return (1);
	}
	print_linked_list(main->env_list);
	return (0);
}
