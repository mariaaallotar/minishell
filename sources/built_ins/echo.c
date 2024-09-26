/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:52:20 by maheleni          #+#    #+#             */
/*   Updated: 2024/09/26 10:55:18 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char **command)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 0;
	if (command[i] == NULL)
	{
		printf("First string NULL\n");
		//error
		return ;
	}
	i = 1;
	if (ft_strncmp(command[i], "-n\0", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (command[i] != NULL)
	{
		printf("%s", command[i]);
		i++;
		if (command[i] == NULL && new_line)
			printf("\n");
		else if (command[i] == NULL)
			break;
		else
			printf(" ");
	}
}
