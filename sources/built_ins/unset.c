/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:33:42 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/30 11:37:51 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset(t_main *main, t_tokens token)
{
	int		i;

	i = 1;
	while (token.command[i] != NULL)
	{
		if (find_node(main, token.command[i]) == NULL)
		{
			i++;
			continue ;
		}
		remove_variable(main, token.command[i]);
		i++;
	}
	return (0);
}
