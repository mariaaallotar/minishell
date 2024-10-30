/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:33:07 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/30 10:11:35 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	existing_key(t_main *main, char *var)
{
	if (find_node(main, var) != NULL)
		return (1);
	return (0);
}

int	forbidden_key(char *var)
{
	int	i;

	if (ft_isdigit(var[0]) || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (1);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) || var[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

int	print_forbidden_key(char *argument)
{
	char	*message;

	message = "export: not a valid identifier: ";
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, argument, ft_strlen(argument));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	export(t_main *main, t_tokens token)
{
	int	i;
	int	return_value;

	return_value = 0;
	if (token.command[1] == NULL)
		return (export_without_args(main));
	i = 1;
	while (token.command[i] != NULL)
	{
		if (forbidden_key(token.command[i]))
			return_value = print_forbidden_key(token.command[i]);
		else if (existing_key(main, token.command[i]))
		{
			if (update_variable(main, token.command[i]) != 0)
				return (errno);
		}
		else
		{
			if (add_variable(main, token.command[i]) != 0)
				return (errno);
		}
		i++;
	}
	return (return_value);
}
