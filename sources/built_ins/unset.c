/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:33:42 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/02 10:56:02 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset(t_main *main, t_tokens token)
{
	int		i;

	i = 1;
	if (token.command[1] == NULL)
		return (0);
	while (token.command[i] != NULL)
	{
		if (ft_strchr(token.command[i], '=') != NULL
			|| find_node(main, token.command[i]) == NULL)
		{
			i++;
			continue ;
		}
		remove_variable(main, token.command[i]);
		i++;
	}
	return (0);
}
