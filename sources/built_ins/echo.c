/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:52:20 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/21 11:38:07 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_no_newline_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

void	print_echo_arguments(int i, int has_new_line, t_tokens token)
{
	while (token.command[i] != NULL)
	{
		printf("%s", token.command[i]);
		i++;
		if (token.command[i] == NULL && has_new_line)
			printf("\n");
		else if (token.command[i] == NULL)
			break;
		else
			printf(" ");
	}
}

int	echo(t_main *main, t_tokens token)
{
	int	has_new_line;
	int	i;

	(void)main;
	has_new_line = 1;
	i = 1;
	if (token.command[i] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (has_no_newline_flag(token.command[i]))
	{
		has_new_line = 0;
		i++;
	}
	print_echo_arguments(i, has_new_line, token);
	return (0);
}
