/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:52:20 by maheleni          #+#    #+#             */
/*   Updated: 2024/12/06 18:21:10 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_newline_flag(char *str)
{
	int	i;

	if (!str[0])
		return (0);
	if (str[0] != '-')
		return (0);
	if (str[0] == '-' && !str[1])
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i++] != 'n')
			return (0);
	}
	return (1);
}

void	print_echo_arguments(t_tokens token)
{
	int	i;
	int	newline_flag;

	newline_flag = check_for_newline_flag(token.command[1]);
	i = 1;
	while (token.command[i])
	{
		if (check_for_newline_flag(token.command[i]))
			i++;
		else
		{
			while (token.command[i])
			{
				write(STDOUT_FILENO, token.command[i],
					ft_strlen(token.command[i]));
				i++;
				if (token.command[i])
					write(STDOUT_FILENO, " ", 1);
			}
		}
	}
	if (!newline_flag)
		write(STDOUT_FILENO, "\n", 1);
}

int	echo(t_main *main, t_tokens token)
{
	int	i;

	(void)main;
	i = 1;
	if (token.command[i] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	print_echo_arguments(token);
	return (0);
}
