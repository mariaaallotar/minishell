/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:33:42 by maheleni          #+#    #+#             */
/*   Updated: 2024/11/27 16:15:02 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset(t_main *main, t_tokens token)
{
	int		i;
	char	*temp_variable;

	i = 1;
	if (token.command[1] == NULL)
		return (0);
	temp_variable = ft_strjoin(token.command[i], "=");
	if (temp_variable == NULL)
	{
		perror("unset");
		return (1);
	}
	while (token.command[i] != NULL)
	{
		if (find_node(main, temp_variable) == NULL)
		{
			i++;
			continue ;
		}
		remove_variable(main, temp_variable);
		i++;
	}
	free(temp_variable);
	return (0);
}
