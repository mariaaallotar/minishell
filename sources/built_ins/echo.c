/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:52:20 by maheleni          #+#    #+#             */
/*   Updated: 2024/09/26 11:56:42 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char **tokens)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 0;
	if (tokens[i] == NULL)
	{
		printf("First string NULL\n");
		//error
		return ;
	}
	i = 1;
	if (ft_strncmp(tokens[i], "-n\0", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (tokens[i] != NULL)
	{
		printf("%s", tokens[i]);
		i++;
		if (tokens[i] == NULL && new_line)
			printf("\n");
		else if (tokens[i] == NULL)
			break;
		else
			printf(" ");
	}
}
